#include "cpu.h"
#include "bus.h"
#include <stdio.h>

CPU g_cpu;

void CPU_Init(void)
{
    CPU_CreateInstructionTable();
    g_cpu.interruptsEnabled = false;
    g_cpu.cycles = 0;
    g_cpu.PC = 0x0000;
}

uint32_t CPU_Tick(void)
{
    uint8_t opcode = Bus_ReadMemory(g_cpu.PC++);

    InstructionFn execute = g_cpu.instructionTable[opcode];

    if (execute)
    {
        g_cpu.cycles += execute();
    }

    // printf("opcode = %X\n", opcode);

    return g_cpu.cycles;
}

void CPU_ResetTicks(void)
{
    g_cpu.cycles = 0;
}

void CPU_UpdateFlagCY(uint16_t testVal)
{
    uint8_t F = RegFile_ReadReg(WR_F);

    F &= ~(1 << CARRY);

    if (testVal > 0xFF)
    {
        F |= (1 << CARRY);
    }

    RegFile_WriteReg(F, WR_F);
}

void CPU_UpdateFlagAC(uint8_t testVal)
{
    uint8_t F = RegFile_ReadReg(WR_F);

    F &= ~(1 << AUX);

    if (testVal > 0x0F)
    {
        F |= (1 << AUX);
    }

    RegFile_WriteReg(F, WR_F);
}

void CPU_UpdateFlagZSPAC(uint16_t testVal)
{
    uint8_t F = RegFile_ReadReg(WR_F);

    uint8_t CY = F & (1 << CARRY);

    F = 0;

    if (CY)
    {
        F |= (1 << CARRY);
    }

    if (testVal == 0)
    {
        F |= (1 << ZERO);
    }

    if (testVal & 0x80)
    {
        F |= (1 << SIGN);
    }

    uint8_t testByte = testVal & 0xFF;

    uint8_t P = 0;

    for (uint8_t i = 0; i < 8; ++i)
    {
        P ^= 1 & (testByte >> i);
    }

    if (P)
    {
        F |= (1 << PARITY);
    }

    RegFile_WriteReg(F, WR_F);
}

void CPU_UpdateFlagZSPCYAC(uint16_t testVal)
{
    CPU_UpdateFlagZSPAC(testVal);
    CPU_UpdateFlagCY(testVal);
}

uint8_t LXI(RegisterPair regPair)
{
    uint8_t lower = Bus_ReadMemory(g_cpu.PC++);
    uint8_t upper = Bus_ReadMemory(g_cpu.PC++);

    RegFile_WriteRegPair8(regPair, upper, lower);

    return 10;
}

uint8_t STAX(RegisterPair regPair)
{
    uint16_t rp = RegFile_ReadRegPair(regPair);
    uint8_t A = RegFile_ReadReg(WR_A);

    Bus_WriteMemory(rp, A);

    return 7;
}

uint8_t INX(RegisterPair regPair)
{
    uint16_t rp = RegFile_ReadRegPair(regPair);
    RegFile_WriteRegPair16(regPair, rp + 1);

    return 5;
}

uint8_t INR(WorkRegister reg)
{
    uint8_t r = RegFile_ReadReg(reg);
    uint16_t result = r + 1;
    CPU_UpdateFlagZSPAC(result);
    RegFile_WriteReg(reg, result & 0xFF);

    return 5;
}

uint8_t DCR(WorkRegister reg)
{
    uint8_t r = RegFile_ReadReg(reg);
    uint16_t result = r - 1;
    CPU_UpdateFlagZSPAC(result);
    RegFile_WriteReg(reg, result & 0xFF);

    return 5;
}

uint8_t MVI(WorkRegister reg)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    RegFile_WriteReg(reg, d8);

    return 7;
}

uint8_t DAD(RegisterPair regPair)
{
    uint16_t rp = RegFile_ReadRegPair(regPair);
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    uint16_t result = HL + rp;
    CPU_UpdateFlagCY(result);
    RegFile_WriteRegPair16(RP_HL, result);

    return 10;
}

uint8_t LDAX(RegisterPair regPair)
{
    uint16_t rp = RegFile_ReadRegPair(regPair);
    uint8_t d8 = Bus_ReadMemory(rp);
    RegFile_WriteReg(WR_A, d8);

    return 7;
}

uint8_t DCX(RegisterPair regPair)
{
    uint16_t rp = RegFile_ReadRegPair(regPair);
    RegFile_WriteRegPair16(regPair, rp - 1);

    return 5;
}

uint8_t MOV(WorkRegister dst, WorkRegister src)
{
    RegFile_WriteReg(dst, RegFile_ReadReg(src));
    return 5;
}

uint8_t MOVRM(WorkRegister dst)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);

    RegFile_WriteReg(dst, m);

    return 7;
}

uint8_t MOVMR(WorkRegister src)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    Bus_WriteMemory(HL, RegFile_ReadReg(src));

    return 7;
}

uint8_t ADD(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A + RegFile_ReadReg(reg);
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 4;
}

uint8_t ADC(WorkRegister reg)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A + RegFile_ReadReg(reg) + carry;
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 4;
}

uint8_t SUB(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A - RegFile_ReadReg(reg);
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 4;
}

uint8_t SBB(WorkRegister reg)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A - RegFile_ReadReg(reg) - carry;
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 4;
}

uint8_t ANA(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A & RegFile_ReadReg(reg);
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 4;
}

uint8_t XRA(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A ^ RegFile_ReadReg(reg);
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 4;
}

uint8_t ORA(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A | RegFile_ReadReg(reg);
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 4;
}

uint8_t CMP(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint8_t r = RegFile_ReadReg(reg);
    CPU_UpdateFlagZSPCYAC(A - r);

    return 4;
}

uint8_t POP(RegisterPair regPair)
{
    uint8_t lower = Bus_ReadMemory(g_cpu.SP++);
    uint8_t upper = Bus_ReadMemory(g_cpu.SP++);

    RegFile_WriteRegPair8(regPair, upper, lower);

    return 10;
}

uint8_t JMP(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    g_cpu.PC = (addr_hi << 8) | addr_lo;

    return 10;
}

uint8_t RET(void)
{
    uint8_t pcl = Bus_ReadMemory(g_cpu.SP++);
    uint8_t pch = Bus_ReadMemory(g_cpu.SP++);

    g_cpu.PC = (pch << 8) | pcl;
    return 10;
}

uint8_t CALL(void)
{
    uint8_t PCH = g_cpu.PC >> 8;
    uint8_t PCL = g_cpu.PC & 0xFF;

    Bus_WriteMemory(--g_cpu.SP, PCH);
    Bus_WriteMemory(--g_cpu.SP, PCL);

    JMP();

    return 17;
}

uint8_t PUSH(RegisterPair regPair)
{
    uint8_t upper = Bus_ReadMemory(--g_cpu.SP);
    uint8_t lower = Bus_ReadMemory(--g_cpu.SP);

    RegFile_WriteRegPair8(regPair, upper, lower);

    return 11;
}

uint8_t JMP_IF(CPU_Flag flag, bool cond)
{
    bool flagStatus = RegFile_ReadReg(WR_F) & (1 << flag);

    if (flagStatus == cond)
    {
        return JMP();
    }

    return 10;
}

uint8_t CALL_IF(CPU_Flag flag, bool cond)
{
    bool flagStatus = RegFile_ReadReg(WR_F) & (1 << flag);

    if (flagStatus == cond)
    {
        return CALL();
    }

    return 11;
}

uint8_t RET_IF(CPU_Flag flag, bool cond)
{
    bool flagStatus = RegFile_ReadReg(WR_F) & (1 << flag);

    if (flagStatus == cond)
    {
        return RET();
    }

    return 5;
}

// ---------------------------------------------------------------------------------------

uint8_t NOP(void)
{
    return 4;
}

uint8_t LXIB(void)
{
    return LXI(RP_BC);
}

uint8_t STAXB(void)
{
    return STAX(RP_BC);
}

uint8_t INXB(void)
{
    return INX(RP_BC);
}

uint8_t INRB(void)
{
    return INR(WR_B);
}

uint8_t DCRB(void)
{
    return DCR(WR_B);
}

uint8_t MVIB(void)
{
    return MVI(WR_B);
}

uint8_t RLC(void)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint8_t bit7 = A & 0x80 ? 1 : 0;

    A = (A << 1) | bit7;

    uint8_t F = RegFile_ReadReg(WR_F);
    F &= ~(1 << CARRY);

    if (bit7)
    {
        F |= (1 << CARRY);
    }

    return 4;
}

uint8_t DADB(void)
{
    return DAD(RP_BC);
}

uint8_t LDAXB(void)
{
    return LDAX(RP_BC);
}

uint8_t DCXB(void)
{
    return DCX(RP_BC);
}

uint8_t INRC(void)
{
    return INR(WR_C);
}

uint8_t DCRC(void)
{
    return DCR(WR_C);
}

uint8_t MVIC(void)
{
    return MVI(WR_C);
}

uint8_t RRC(void)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint8_t bit0 = A & 0x01 ? 1 : 0;

    A = (A >> 1) | (bit0 << 7);

    uint8_t F = RegFile_ReadReg(WR_F);
    F &= ~(1 << CARRY);

    if (bit0)
    {
        F |= (1 << CARRY);
    }

    RegFile_WriteReg(F, WR_F);

    return 4;
}

uint8_t LXID(void)
{
    return LXI(RP_DE);
}

uint8_t STAXD(void)
{
    return STAX(RP_DE);
}

uint8_t INXD(void)
{
    return INX(RP_DE);
}

uint8_t INRD(void)
{
    return INR(WR_D);
}

uint8_t DCRD(void)
{
    return DCR(WR_D);
}

uint8_t MVID(void)
{
    return MVI(WR_D);
}

uint8_t RAL(void)
{
    uint8_t F = RegFile_ReadReg(WR_F);
    uint8_t CY = F & (1 << CARRY);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint8_t bit7 = A & 0x80;

    A = (A << 1) | CY;

    F &= ~(1 << CARRY);

    if (bit7)
    {
        F |= (1 << CARRY);
    }

    RegFile_WriteReg(F, WR_F);

    return 4;
}

uint8_t DADD(void)
{
    return DAD(RP_DE);
}

uint8_t LDAXD(void)
{
    return LDAX(RP_DE);
}

uint8_t DCXD(void)
{
    return DCX(RP_DE);
}

uint8_t INRE(void)
{
    return INR(WR_E);
}

uint8_t DCRE(void)
{
    return DCR(WR_E);
}

uint8_t MVIE(void)
{
    return MVI(WR_E);
}

uint8_t RAR(void)
{
    uint8_t F = RegFile_ReadReg(WR_F);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint8_t bit7 = A & 0x80;
    uint8_t bit0 = A & 0x01;

    A = (A >> 1) | bit7;

    F &= ~(1 << CARRY);

    if (bit0)
    {
        F |= (1 << CARRY);
    }

    RegFile_WriteReg(F, WR_F);

    return 4;
}

uint8_t LXIH(void)
{
    return LXI(RP_HL);
}

uint8_t SHLD(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    uint16_t addr = (addr_hi << 8) | addr_lo;

    uint8_t H = RegFile_ReadReg(WR_H);
    uint8_t L = RegFile_ReadReg(WR_L);

    Bus_WriteMemory(addr, L);
    Bus_WriteMemory(addr + 1, H);

    return 16;
}

uint8_t INXH(void)
{
    return INX(RP_HL);
}

uint8_t INRH(void)
{
    return INR(WR_H);
}

uint8_t DCRH(void)
{
    return DCR(WR_H);
}

uint8_t MVIH(void)
{
    return MVI(WR_H);
}

uint8_t DAA(void)
{
    return 4;
}

uint8_t DADH(void)
{
    return DAD(RP_HL);
}

uint8_t LHLD(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    uint16_t addr = (addr_hi << 8) | addr_lo;

    RegFile_WriteReg(WR_L, Bus_ReadMemory(addr));
    RegFile_WriteReg(WR_H, Bus_ReadMemory(addr + 1));

    return 16;
}

uint8_t DCXH(void)
{
    return DCX(RP_HL);
}

uint8_t INRL(void)
{
    return INR(WR_L);
}

uint8_t DCRL(void)
{
    return DCR(WR_L);
}

uint8_t MVIL(void)
{
    return MVI(WR_L);
}

uint8_t CMA(void)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, ~A);

    return 4;
}

uint8_t LXISP(void)
{
    uint8_t byte_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t byte_hi = Bus_ReadMemory(g_cpu.PC++);

    g_cpu.SP = (byte_hi << 8) | byte_lo;

    return 10;
}

uint8_t STA(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    uint16_t addr = (addr_hi << 8) | addr_lo;
    uint8_t A = RegFile_ReadReg(WR_A);

    Bus_WriteMemory(addr, A);

    return 13;
}

uint8_t INXSP(void)
{
    g_cpu.SP++;

    return 5;
}

uint8_t INRM(void)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);

    uint8_t m = Bus_ReadMemory(HL);
    Bus_WriteMemory(HL, m + 1);

    return 10;
}

uint8_t DCRM(void)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);

    uint8_t m = Bus_ReadMemory(HL);
    Bus_WriteMemory(HL, m - 1);

    return 10;
}

uint8_t MVIM(void)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);

    Bus_WriteMemory(HL, d8);

    return 10;
}

uint8_t STC(void)
{
    uint8_t F = RegFile_ReadReg(WR_F);
    F |= (1 << CARRY);
    RegFile_WriteReg(WR_F, F);

    return 4;
}

uint8_t DADSP(void)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    uint16_t result = HL + g_cpu.SP;
    CPU_UpdateFlagCY(result);
    RegFile_WriteRegPair16(RP_HL, result);

    return 10;
}

uint8_t LDA(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    uint16_t addr = (addr_hi << 8) | addr_lo;

    RegFile_WriteReg(WR_A, Bus_ReadMemory(addr));

    return 13;
}

uint8_t DCXSP(void)
{
    g_cpu.SP--;

    return 5;
}

uint8_t INRA(void)
{
    return INR(WR_A);
}

uint8_t DCRA(void)
{
    return DCR(WR_A);
}

uint8_t MVIA(void)
{
    return MVI(WR_A);
}

uint8_t CMC(void)
{
    uint8_t F = RegFile_ReadReg(WR_F);

    if (F & (1 << CARRY))
    {
        F &= ~(1 << CARRY);
    }
    else
    {
        F |= (1 << CARRY);
    }

    RegFile_WriteReg(WR_F, F);

    return 4;
}

uint8_t MOVBB(void)
{
    return MOV(WR_B, WR_B);
}

uint8_t MOVBC(void)
{
    return MOV(WR_B, WR_C);
}

uint8_t MOVBD(void)
{
    return MOV(WR_B, WR_D);
}

uint8_t MOVBE(void)
{
    return MOV(WR_B, WR_E);
}

uint8_t MOVBH(void)
{
    return MOV(WR_B, WR_H);
}

uint8_t MOVBL(void)
{
    return MOV(WR_B, WR_L);
}

uint8_t MOVBM(void)
{
    return MOVRM(WR_B);
}

uint8_t MOVBA(void)
{
    return MOV(WR_B, WR_A);
}

uint8_t MOVCB(void)
{
    return MOV(WR_C, WR_B);
}

uint8_t MOVCC(void)
{
    return MOV(WR_C, WR_C);
}

uint8_t MOVCD(void)
{
    return MOV(WR_C, WR_D);
}

uint8_t MOVCE(void)
{
    return MOV(WR_C, WR_E);
}

uint8_t MOVCH(void)
{
    return MOV(WR_C, WR_H);
}

uint8_t MOVCL(void)
{
    return MOV(WR_C, WR_L);
}

uint8_t MOVCM(void)
{
    return MOVRM(WR_C);
}

uint8_t MOVCA(void)
{
    return MOV(WR_C, WR_A);
}

uint8_t MOVDB(void)
{
    return MOV(WR_D, WR_B);
}

uint8_t MOVDC(void)
{
    return MOV(WR_D, WR_C);
}

uint8_t MOVDD(void)
{
    return MOV(WR_D, WR_D);
}

uint8_t MOVDE(void)
{
    return MOV(WR_D, WR_E);
}

uint8_t MOVDH(void)
{
    return MOV(WR_D, WR_H);
}

uint8_t MOVDL(void)
{
    return MOV(WR_D, WR_L);
}

uint8_t MOVDM(void)
{
    return MOVRM(WR_D);
}

uint8_t MOVDA(void)
{
    return MOV(WR_D, WR_A);
}

uint8_t MOVEB(void)
{
    return MOV(WR_E, WR_B);
}

uint8_t MOVEC(void)
{
    return MOV(WR_E, WR_C);
}

uint8_t MOVED(void)
{
    return MOV(WR_E, WR_D);
}

uint8_t MOVEE(void)
{
    return MOV(WR_E, WR_E);
}

uint8_t MOVEH(void)
{
    return MOV(WR_E, WR_H);
}

uint8_t MOVEL(void)
{
    return MOV(WR_E, WR_L);
}

uint8_t MOVEM(void)
{
    return MOVRM(WR_E);
}

uint8_t MOVEA(void)
{
    return MOV(WR_E, WR_A);
}

uint8_t MOVHB(void)
{
    return MOV(WR_H, WR_B);
}

uint8_t MOVHC(void)
{
    return MOV(WR_H, WR_C);
}

uint8_t MOVHD(void)
{
    return MOV(WR_H, WR_D);
}

uint8_t MOVHE(void)
{
    return MOV(WR_H, WR_E);
}

uint8_t MOVHH(void)
{
    return MOV(WR_H, WR_H);
}

uint8_t MOVHL(void)
{
    return MOV(WR_H, WR_L);
}

uint8_t MOVHM(void)
{
    return MOVRM(WR_H);
}

uint8_t MOVHA(void)
{
    return MOV(WR_H, WR_A);
}

uint8_t MOVLB(void)
{
    return MOV(WR_L, WR_B);
}

uint8_t MOVLC(void)
{
    return MOV(WR_L, WR_C);
}

uint8_t MOVLD(void)
{
    return MOV(WR_L, WR_D);
}

uint8_t MOVLE(void)
{
    return MOV(WR_L, WR_E);
}

uint8_t MOVLH(void)
{
    return MOV(WR_L, WR_H);
}

uint8_t MOVLL(void)
{
    return MOV(WR_L, WR_L);
}

uint8_t MOVLM(void)
{
    return MOVRM(WR_L);
}

uint8_t MOVLA(void)
{
    return MOV(WR_L, WR_A);
}

uint8_t MOVMB(void)
{
    return MOVMR(WR_B);
}

uint8_t MOVMC(void)
{
    return MOVMR(WR_C);
}

uint8_t MOVMD(void)
{
    return MOVMR(WR_D);
}

uint8_t MOVME(void)
{
    return MOVMR(WR_E);
}

uint8_t MOVMH(void)
{
    return MOVMR(WR_H);
}

uint8_t MOVML(void)
{
    return MOVMR(WR_L);
}

uint8_t HLT(void)
{
    return 7;
}

uint8_t MOVMA(void)
{
    return MOVMR(WR_A);
}

uint8_t MOVAB(void)
{
    return MOV(WR_A, WR_B);
}

uint8_t MOVAC(void)
{
    return MOV(WR_A, WR_C);
}

uint8_t MOVAD(void)
{
    return MOV(WR_A, WR_D);
}

uint8_t MOVAE(void)
{
    return MOV(WR_A, WR_E);
}

uint8_t MOVAH(void)
{
    return MOV(WR_A, WR_H);
}

uint8_t MOVAL(void)
{
    return MOV(WR_A, WR_L);
}

uint8_t MOVAM(void)
{
    return MOVRM(WR_A);
}

uint8_t MOVAA(void)
{
    return MOV(WR_A, WR_A);
}

uint8_t ADDB(void)
{
    return ADD(WR_B);
}

uint8_t ADDC(void)
{
    return ADD(WR_C);
}

uint8_t ADDD(void)
{
    return ADD(WR_D);
}

uint8_t ADDE(void)
{
    return ADD(WR_E);
}

uint8_t ADDH(void)
{
    return ADD(WR_H);
}

uint8_t ADDL(void)
{
    return ADD(WR_L);
}

uint8_t ADDM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, A + m);

    return 7;
}

uint8_t ADDA(void)
{
    return ADD(WR_A);
}

uint8_t ADCB(void)
{
    return ADC(WR_B);
}

uint8_t ADCC(void)
{
    return ADC(WR_C);
}

uint8_t ADCD(void)
{
    return ADC(WR_D);
}

uint8_t ADCE(void)
{
    return ADC(WR_E);
}

uint8_t ADCH(void)
{
    return ADC(WR_H);
}

uint8_t ADCL(void)
{
    return ADC(WR_L);
}

uint8_t ADCM(void)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t m = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);

    RegFile_WriteReg(WR_A, A + m + carry);

    return 7;
}

uint8_t ADCA(void)
{
    return ADC(WR_A);
}

uint8_t SUBB(void)
{
    return SUB(WR_B);
}

uint8_t SUBC(void)
{
    return SUB(WR_C);
}

uint8_t SUBD(void)
{
    return SUB(WR_D);
}

uint8_t SUBE(void)
{
    return SUB(WR_E);
}

uint8_t SUBH(void)
{
    return SUB(WR_H);
}

uint8_t SUBL(void)
{
    return SUB(WR_L);
}

uint8_t SUBM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, A - m);

    return 7;
}

uint8_t SUBA(void)
{
    return SUB(WR_A);
}

uint8_t SBBB(void)
{
    return SBB(WR_B);
}

uint8_t SBBC(void)
{
    return SBB(WR_C);
}

uint8_t SBBD(void)
{
    return SBB(WR_D);
}

uint8_t SBBE(void)
{
    return SBB(WR_E);
}

uint8_t SBBH(void)
{
    return SBB(WR_H);
}

uint8_t SBBL(void)
{
    return SBB(WR_L);
}

uint8_t SBBM(void)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t m = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);

    RegFile_WriteReg(WR_A, A - m - carry);

    return 7;
}

uint8_t SBBA(void)
{
    return SBB(WR_A);
}

uint8_t ANAB(void)
{
    return ANA(WR_B);
}

uint8_t ANAC(void)
{
    return ANA(WR_C);
}

uint8_t ANAD(void)
{
    return ANA(WR_D);
}

uint8_t ANAE(void)
{
    return ANA(WR_E);
}

uint8_t ANAH(void)
{
    return ANA(WR_H);
}

uint8_t ANAL(void)
{
    return ANA(WR_L);
}

uint8_t ANAM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, A & m);

    return 7;
}

uint8_t ANAA(void)
{
    return ANA(WR_A);
}

uint8_t XRAB(void)
{
    return XRA(WR_B);
}

uint8_t XRAC(void)
{
    return XRA(WR_C);
}

uint8_t XRAD(void)
{
    return XRA(WR_D);
}

uint8_t XRAE(void)
{
    return XRA(WR_E);
}

uint8_t XRAH(void)
{
    return XRA(WR_H);
}

uint8_t XRAL(void)
{
    return XRA(WR_L);
}

uint8_t XRAM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, A ^ m);

    return 7;
}

uint8_t XRAA(void)
{
    return XRA(WR_A);
}

uint8_t ORAB(void)
{
    return ORA(WR_B);
}

uint8_t ORAC(void)
{
    return ORA(WR_C);
}

uint8_t ORAD(void)
{
    return ORA(WR_D);
}

uint8_t ORAE(void)
{
    return ORA(WR_E);
}

uint8_t ORAH(void)
{
    return ORA(WR_H);
}

uint8_t ORAL(void)
{
    return ORA(WR_L);
}

uint8_t ORAM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, A | m);

    return 7;
}

uint8_t ORAA(void)
{
    return ORA(WR_A);
}

uint8_t CMPB(void)
{
    return CMP(WR_B);
}

uint8_t CMPC(void)
{
    return CMP(WR_C);
}

uint8_t CMPD(void)
{
    return CMP(WR_D);
}

uint8_t CMPE(void)
{
    return CMP(WR_E);
}

uint8_t CMPH(void)
{
    return CMP(WR_H);
}

uint8_t CMPL(void)
{
    return CMP(WR_L);
}

uint8_t CMPM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);

    CPU_UpdateFlagZSPCYAC(A - m);

    return 7;
}

uint8_t CMPA(void)
{
    return CMP(WR_A);
}

uint8_t RNZ(void)
{
    return RET_IF(ZERO, false);
}

uint8_t POPB(void)
{
    return POP(RP_BC);
}

uint8_t JNZ(void)
{
    return JMP_IF(ZERO, false);
}

uint8_t CNZ(void)
{
    return CALL_IF(ZERO, false);
}

uint8_t PUSHB(void)
{
    return PUSH(RP_BC);
}

uint8_t ADI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A + d8;
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 7;
}

uint8_t RZ(void)
{
    return RET_IF(ZERO, true);
}

uint8_t JZ(void)
{
    return JMP_IF(ZERO, true);
}

uint8_t CZ(void)
{
    return CALL_IF(ZERO, true);
}

uint8_t ACI(void)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A + d8 + carry;
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 7;
}

uint8_t RNC(void)
{
    return RET_IF(CARRY, false);
}

uint8_t POPD(void)
{
    return POP(RP_DE);
}

uint8_t JNC(void)
{
    return JMP_IF(CARRY, false);
}

uint8_t OUT(void)
{
    uint8_t port = Bus_ReadMemory(g_cpu.PC++);
    Bus_WritePort((IoPort)port, RegFile_ReadReg(WR_A));

    return 10;
}

uint8_t CNC(void)
{
    return CALL_IF(CARRY, false);
}

uint8_t PUSHD(void)
{
    return PUSH(RP_DE);
}

uint8_t SUI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A - d8;
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 7;
}

uint8_t RC(void)
{
    return RET_IF(CARRY, true);
}

uint8_t JC(void)
{
    return JMP_IF(CARRY, true);
}

uint8_t IN(void)
{
    uint8_t port = Bus_ReadMemory(g_cpu.PC++);
    RegFile_WriteReg(WR_A, Bus_ReadPort((IoPort)port));

    return 10;
}

uint8_t CC(void)
{
    return CALL_IF(CARRY, true);
}

uint8_t SBI(void)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A - d8 - carry;
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 7;
}

uint8_t RPO(void)
{
    return RET_IF(PARITY, true);
}

uint8_t POPH(void)
{
    return POP(RP_HL);
}

uint8_t JPO(void)
{
    return JMP_IF(PARITY, true);
}

uint8_t XTHL(void)
{
    uint8_t H = RegFile_ReadReg(WR_H);
    uint8_t L = RegFile_ReadReg(WR_L);

    RegFile_WriteReg(WR_L, Bus_ReadMemory(g_cpu.SP));
    RegFile_WriteReg(WR_H, Bus_ReadMemory(g_cpu.SP + 1));

    Bus_WriteMemory(g_cpu.SP, L);
    Bus_WriteMemory(g_cpu.SP + 1, H);

    return 18;
}

uint8_t CPO(void)
{
    return CALL_IF(PARITY, true);
}

uint8_t PUSHH(void)
{
    return PUSH(RP_HL);
}

uint8_t ANI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A & d8;
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 7;
}

uint8_t RPE(void)
{
    return RET_IF(PARITY, false);
}

uint8_t PCHL(void)
{
    g_cpu.PC = RegFile_ReadRegPair(RP_HL);
    return 5;
}

uint8_t JPE(void)
{
    return JMP_IF(PARITY, false);
}

uint8_t XCHG(void)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    uint16_t DE = RegFile_ReadRegPair(RP_DE);

    RegFile_WriteRegPair16(RP_HL, DE);
    RegFile_WriteRegPair16(RP_DE, HL);

    return 5;
}

uint8_t CPE(void)
{
    return CALL_IF(PARITY, false);
}

uint8_t XRI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A ^ d8;
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 7;
}

uint8_t RP(void)
{
    return RET_IF(SIGN, false);
}

uint8_t POPPSW(void)
{
    return POP(RP_PSW);
}

uint8_t JP(void)
{
    return JMP_IF(SIGN, false);
}

uint8_t DI(void)
{
    g_cpu.interruptsEnabled = false;

    return 4;
}

uint8_t CP(void)
{
    return CALL_IF(SIGN, false);
}

uint8_t PUSHPSW(void)
{
    return PUSH(RP_PSW);
}

uint8_t ORI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A | d8;
    CPU_UpdateFlagZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);

    return 7;
}

uint8_t RM(void)
{
    return RET_IF(SIGN, true);
}

uint8_t SPHL(void)
{
    g_cpu.SP = RegFile_ReadRegPair(RP_HL);
    return 5;
}

uint8_t JM(void)
{
    return JMP_IF(SIGN, true);
}

uint8_t EI(void)
{
    g_cpu.interruptsEnabled = true;
    return 7;
}

uint8_t CM(void)
{
    return CALL_IF(SIGN, true);
}

uint8_t CPI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    CPU_UpdateFlagZSPCYAC(A - d8);
    return 7;
}
