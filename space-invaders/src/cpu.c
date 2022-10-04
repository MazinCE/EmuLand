#include "cpu.h"
#include "bus.h"

void CPU_Init(void) {}
void CPU_CreateInstructionTable(void) {}

void CPU_AlterCY(uint16_t testVal)
{
    uint8_t F = RegFile_ReadReg(WR_F);

    F &= ~(1 << CARRY);

    if (testVal > 0xFF)
    {
        F |= (1 << CARRY);
    }

    RegFile_WriteReg(F, WR_F);
}

void CPU_AlterAC(uint8_t testVal)
{
    uint8_t F = RegFile_ReadReg(WR_F);

    F &= ~(1 << AUX);

    if (testVal > 0x0F)
    {
        F |= (1 << AUX);
    }

    RegFile_WriteReg(F, WR_F);
}

void CPU_AlterZSPAC(uint16_t testVal)
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

void CPU_AlterZSPCYAC(uint16_t testVal)
{
    CPU_AlterZSPAC(testVal);
    CPU_AlterCY(testVal);
}

void LXI(RegisterPair regPair)
{
    uint8_t lower = Bus_ReadMemory(g_cpu.PC++);
    uint8_t upper = Bus_ReadMemory(g_cpu.PC++);

    RegFile_WriteRegPair8(regPair, upper, lower);
}

void STAX(RegisterPair regPair)
{
    uint16_t rp = RegFile_ReadRegPair(regPair);
    uint8_t A = RegFile_ReadReg(WR_A);

    Bus_WriteMemory(rp, A);
}

void INX(RegisterPair regPair)
{
    uint16_t rp = RegFile_ReadRegPair(regPair);
    RegFile_WriteRegPair16(regPair, rp + 1);
}

void INR(WorkRegister reg)
{
    uint8_t r = RegFile_ReadReg(reg);
    uint16_t result = r + 1;
    CPU_AlterZSPAC(result);
    RegFile_WriteReg(reg, result & 0xFF);
}

void DCR(WorkRegister reg)
{
    uint8_t r = RegFile_ReadReg(reg);
    uint16_t result = r - 1;
    CPU_AlterZSPAC(result);
    RegFile_WriteReg(reg, result & 0xFF);
}

void MVI(WorkRegister reg)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    RegFile_WriteReg(reg, d8);
}

void DAD(RegisterPair regPair)
{
    uint16_t rp = RegFile_ReadRegPair(regPair);
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    uint16_t result = HL + rp;
    CPU_AlterCY(result);
    RegFile_WriteRegPair16(RP_HL, result);
}

void LDAX(RegisterPair regPair)
{
    uint16_t rp = RegFile_ReadRegPair(regPair);
    uint8_t d8 = Bus_ReadMemory(rp);
    RegFile_WriteReg(WR_A, d8);
}

void DCX(RegisterPair regPair)
{
    uint16_t rp = RegFile_ReadRegPair(regPair);
    RegFile_WriteRegPair16(regPair, rp - 1);
}

void MOV(WorkRegister dst, WorkRegister src)
{
    RegFile_WriteReg(dst, RegFile_ReadReg(src));
}

void MOVRM(WorkRegister dst)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);

    RegFile_WriteReg(dst, m);
}

void MOVMR(WorkRegister src)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    Bus_WriteMemory(HL, RegFile_ReadReg(src));
}

void ADD(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A + RegFile_ReadReg(reg);
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void ADC(WorkRegister reg)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A + RegFile_ReadReg(reg) + carry;
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void SUB(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A - RegFile_ReadReg(reg);
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void SBB(WorkRegister reg)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A - RegFile_ReadReg(reg) - carry;
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void ANA(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A & RegFile_ReadReg(reg);
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void XRA(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A ^ RegFile_ReadReg(reg);
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void ORA(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A | RegFile_ReadReg(reg);
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void CMP(WorkRegister reg)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    uint8_t r = RegFile_ReadReg(reg);
    CPU_AlterZSPCYAC(A - r);
}

void POP(RegisterPair regPair)
{
    uint8_t lower = Bus_ReadMemory(g_cpu.SP++);
    uint8_t upper = Bus_ReadMemory(g_cpu.SP++);

    RegFile_WriteRegPair8(regPair, upper, lower);
}

void JMP(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    g_cpu.PC = (addr_hi << 8) | addr_lo;
}

void CALL(void)
{
    uint8_t PCH = g_cpu.PC >> 8;
    uint8_t PCL = g_cpu.PC & 0xFF;

    Bus_WriteMemory(--g_cpu.SP, PCH);
    Bus_WriteMemory(--g_cpu.SP, PCL);

    JMP();
}

void PUSH(RegisterPair regPair)
{
    uint8_t upper = Bus_ReadMemory(--g_cpu.SP);
    uint8_t lower = Bus_ReadMemory(--g_cpu.SP);

    RegFile_WriteRegPair8(regPair, upper, lower);
}

void JMP_IF(CPU_Flag flag, bool cond)
{
    bool flagStatus = RegFile_ReadReg(WR_F) & (1 << flag);

    if (flagStatus == cond)
    {
        JMP();
    }
}

void CALL_IF(CPU_Flag flag, bool cond)
{
    bool flagStatus = RegFile_ReadReg(WR_F) & (1 << flag);

    if (flagStatus == cond)
    {
        CALL();
    }
}

void RET_IF(CPU_Flag flag, bool cond)
{
    bool flagStatus = RegFile_ReadReg(WR_F) & (1 << flag);

    if (flagStatus == cond)
    {
        RET();
    }
}

// ---------------------------------------------------------------------------------------

void NOP(void)
{
}

void LXIB(void)
{
    LXI(RP_BC);
}

void STAXB(void)
{
    STAX(RP_BC);
}

void INXB(void)
{
    INX(RP_BC);
}

void INRB(void)
{
    INR(WR_B);
}

void DCRB(void)
{
    DCR(WR_B);
}

void MVIB(void)
{
    MVI(WR_B);
}

void RLC(void)
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
}

void DADB(void)
{
    DAD(RP_BC);
}

void LDAXB(void)
{
    LDAX(RP_BC);
}

void DCXB(void)
{
    DCX(RP_BC);
}

void INRC(void)
{
    INR(WR_C);
}

void DCRC(void)
{
    DCR(WR_C);
}

void MVIC(void)
{
    MVI(WR_C);
}

void RRC(void)
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
}

void LXID(void)
{
    LXI(RP_DE);
}

void STAXD(void)
{
    STAX(RP_DE);
}

void INXD(void)
{
    INX(RP_DE);
}

void INRD(void)
{
    INR(WR_D);
}

void DCRD(void)
{
    DCR(WR_D);
}

void MVID(void)
{
    MVI(WR_D);
}

void RAL(void)
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
}

void DADD(void)
{
    DAD(RP_DE);
}

void LDAXD(void)
{
    LDAX(RP_DE);
}

void DCXD(void)
{
    DCX(RP_DE);
}

void INRE(void)
{
    INR(WR_E);
}

void DCRE(void)
{
    DCR(WR_E);
}

void MVIE(void)
{
    MVI(WR_E);
}

void RAR(void)
{
    uint8_t F = RegFile_ReadReg(WR_F);
    uint8_t CY = F & (1 << CARRY);
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
}

void LXIH(void)
{
    LXI(RP_HL);
}

void SHLD(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    uint16_t addr = (addr_hi << 8) | addr_lo;

    uint8_t H = RegFile_ReadReg(WR_H);
    uint8_t L = RegFile_ReadReg(WR_L);

    Bus_WriteMemory(addr, L);
    Bus_WriteMemory(addr + 1, H);
}

void INXH(void)
{
    INX(RP_HL);
}

void INRH(void)
{
    INR(WR_H);
}

void DCRH(void)
{
    DCR(WR_H);
}

void MVIH(void)
{
    MVI(WR_H);
}

void DAA(void)
{
}

void DADH(void)
{
    DAD(RP_HL);
}

void LHLD(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    uint16_t addr = (addr_hi << 8) | addr_lo;

    RegFile_WriteReg(WR_L, Bus_ReadMemory(addr));
    RegFile_WriteReg(WR_H, Bus_ReadMemory(addr + 1));
}

void DCXH(void)
{
    DCX(RP_HL);
}

void INRL(void)
{
    INR(WR_L);
}

void DCRL(void)
{
    DCR(WR_L);
}

void MVIL(void)
{
    MVI(WR_L);
}

void CMA(void)
{
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, ~A);
}

void LXISP(void)
{
    uint8_t byte_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t byte_hi = Bus_ReadMemory(g_cpu.PC++);

    g_cpu.SP = (byte_hi << 8) | byte_lo;
}

void STA(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    uint16_t addr = (addr_hi << 8) | addr_lo;
    uint8_t A = RegFile_ReadReg(WR_A);

    Bus_WriteMemory(addr, A);
}

void INXSP(void)
{
    g_cpu.SP++;
}

void INRM(void)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);

    uint8_t m = Bus_ReadMemory(HL);
    Bus_WriteMemory(HL, m + 1);
}

void DCRM(void)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);

    uint8_t m = Bus_ReadMemory(HL);
    Bus_WriteMemory(HL, m - 1);
}

void MVIM(void)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);

    Bus_WriteMemory(HL, d8);
}

void STC(void)
{
    uint8_t F = RegFile_ReadReg(WR_F);
    F |= (1 << CARRY);
    RegFile_WriteReg(WR_F, F);
}

void DADSP(void)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    uint16_t result = HL + g_cpu.SP;
    CPU_AlterCY(result);
    RegFile_WriteRegPair16(RP_HL, result);
}

void LDA(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    uint16_t addr = (addr_hi << 8) | addr_lo;

    RegFile_WriteReg(WR_A, Bus_ReadMemory(addr));
}

void DCXSP(void)
{
    g_cpu.SP--;
}

void INRA(void)
{
    INR(WR_A);
}

void DCRA(void)
{
    DCR(WR_A);
}

void MVIA(void)
{
    MVI(WR_A);
}

void CMC(void)
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
}

void MOVBB(void)
{
    MOV(WR_B, WR_B);
}

void MOVBC(void)
{
    MOV(WR_B, WR_C);
}

void MOVBD(void)
{
    MOV(WR_B, WR_D);
}

void MOVBE(void)
{
    MOV(WR_B, WR_E);
}

void MOVBH(void)
{
    MOV(WR_B, WR_H);
}

void MOVBL(void)
{
    MOV(WR_B, WR_L);
}

void MOVBM(void)
{
    MOVRM(WR_B);
}

void MOVBA(void)
{
    MOV(WR_B, WR_A);
}

void MOVCB(void)
{
    MOV(WR_C, WR_B);
}

void MOVCC(void)
{
    MOV(WR_C, WR_C);
}

void MOVCD(void)
{
    MOV(WR_C, WR_D);
}

void MOVCE(void)
{
    MOV(WR_C, WR_E);
}

void MOVCH(void)
{
    MOV(WR_C, WR_H);
}

void MOVCL(void)
{
    MOV(WR_C, WR_L);
}

void MOVCM(void)
{
    MOVRM(WR_C);
}

void MOVCA(void)
{
    MOV(WR_C, WR_A);
}

void MOVDB(void)
{
    MOV(WR_D, WR_B);
}

void MOVDC(void)
{
    MOV(WR_D, WR_C);
}

void MOVDD(void)
{
    MOV(WR_D, WR_D);
}

void MOVDE(void)
{
    MOV(WR_D, WR_E);
}

void MOVDH(void)
{
    MOV(WR_D, WR_H);
}

void MOVDL(void)
{
    MOV(WR_D, WR_L);
}

void MOVDM(void)
{
    MOVRM(WR_D);
}

void MOVDA(void)
{
    MOV(WR_D, WR_A);
}

void MOVEB(void)
{
    MOV(WR_E, WR_B);
}

void MOVEC(void)
{
    MOV(WR_E, WR_C);
}

void MOVED(void)
{
    MOV(WR_E, WR_D);
}

void MOVEE(void)
{
    MOV(WR_E, WR_E);
}

void MOVEH(void)
{
    MOV(WR_E, WR_H);
}

void MOVEL(void)
{
    MOV(WR_E, WR_L);
}

void MOVEM(void)
{
    MOVRM(WR_E);
}

void MOVEA(void)
{
    MOV(WR_E, WR_A);
}

void MOVHB(void)
{
    MOV(WR_H, WR_B);
}

void MOVHC(void)
{
    MOV(WR_H, WR_C);
}

void MOVHD(void)
{
    MOV(WR_H, WR_D);
}

void MOVHE(void)
{
    MOV(WR_H, WR_E);
}

void MOVHH(void)
{
    MOV(WR_H, WR_H);
}

void MOVHL(void)
{
    MOV(WR_H, WR_L);
}

void MOVHM(void)
{
    MOVRM(WR_H);
}

void MOVHA(void)
{
    MOV(WR_H, WR_A);
}

void MOVLB(void)
{
    MOV(WR_L, WR_B);
}

void MOVLC(void)
{
    MOV(WR_L, WR_C);
}

void MOVLD(void)
{
    MOV(WR_L, WR_D);
}

void MOVLE(void)
{
    MOV(WR_L, WR_E);
}

void MOVLH(void)
{
    MOV(WR_L, WR_H);
}

void MOVLL(void)
{
    MOV(WR_L, WR_L);
}

void MOVLM(void)
{
    MOVRM(WR_L);
}

void MOVLA(void)
{
    MOV(WR_L, WR_A);
}

void MOVMB(void)
{
    MOVMR(WR_B);
}

void MOVMC(void)
{
    MOVMR(WR_C);
}

void MOVMD(void)
{
    MOVMR(WR_D);
}

void MOVME(void)
{
    MOVMR(WR_E);
}

void MOVMH(void)
{
    MOVMR(WR_H);
}

void MOVML(void)
{
    MOVMR(WR_L);
}

void HLT(void) {}

void MOVMA(void)
{
    MOVMR(WR_A);
}

void MOVAB(void)
{
    MOV(WR_A, WR_B);
}

void MOVAC(void)
{
    MOV(WR_A, WR_C);
}

void MOVAD(void)
{
    MOV(WR_A, WR_D);
}

void MOVAE(void)
{
    MOV(WR_A, WR_E);
}

void MOVAH(void)
{
    MOVMR(WR_A, WR_H);
}

void MOVAL(void)
{
    MOV(WR_A, WR_L);
}

void MOVAM(void)
{
    MOVRM(WR_A);
}

void MOVAA(void)
{
    MOV(WR_A, WR_A);
}

void ADDB(void)
{
    ADD(WR_B);
}

void ADDC(void)
{
    ADD(WR_C);
}

void ADDD(void)
{
    ADD(WR_D);
}

void ADDE(void)
{
    ADD(WR_E);
}

void ADDH(void)
{
    ADD(WR_H);
}

void ADDL(void)
{
    ADD(WR_L);
}

void ADDM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, A + m);
}

void ADDA(void)
{
    ADD(WR_A);
}

void ADCB(void)
{
    ADC(WR_B);
}

void ADCC(void)
{
    ADC(WR_C);
}

void ADCD(void)
{
    ADC(WR_D);
}

void ADCE(void)
{
    ADC(WR_E);
}

void ADCH(void)
{
    ADC(WR_H);
}

void ADCL(void)
{
    ADC(WR_L);
}

void ADCM(void)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t m = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);

    RegFile_WriteReg(WR_A, A + m + carry);
}

void ADCA(void)
{
    ADC(WR_A);
}

void SUBB(void)
{
    SUB(WR_B);
}

void SUBC(void)
{
    SUB(WR_C);
}

void SUBD(void)
{
    SUB(WR_D);
}

void SUBE(void)
{
    SUB(WR_E);
}

void SUBH(void)
{
    SUB(WR_H);
}

void SUBL(void)
{
    SUB(WR_L);
}

void SUBM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, A - m);
}

void SUBA(void)
{
    SUB(WR_A);
}

void SBBB(void)
{
    SBB(WR_B);
}

void SBBC(void)
{
    SBB(WR_C);
}

void SBBD(void)
{
    SBB(WR_D);
}

void SBBE(void)
{
    SBB(WR_E);
}

void SBBH(void)
{
    SBB(WR_H);
}

void SBBL(void)
{
    SBB(WR_L);
}

void SBBM(void)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t m = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);

    RegFile_WriteReg(WR_A, A - m - carry);
}

void SBBA(void)
{
    SBB(WR_A);
}

void ANAB(void)
{
    ANA(WR_B);
}

void ANAC(void)
{
    ANA(WR_C);
}

void ANAD(void)
{
    ANA(WR_D);
}

void ANAE(void)
{
    ANA(WR_E);
}

void ANAH(void)
{
    ANA(WR_H);
}

void ANAL(void)
{
    ANA(WR_L);
}

void ANAM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, A & m);
}

void ANAA(void)
{
    ANA(WR_A);
}

void XRAB(void)
{
    XRA(WR_B);
}

void XRAC(void)
{
    XRA(WR_C);
}

void XRAD(void)
{
    XRA(WR_D);
}

void XRAE(void)
{
    XRA(WR_E);
}

void XRAH(void)
{
    XRA(WR_H);
}

void XRAL(void)
{
    XRA(WR_L);
}

void XRAM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, A ^ m);
}

void XRAA(void)
{
    XRA(WR_A);
}

void ORAB(void)
{
    ORA(WR_B);
}

void ORAC(void)
{
    ORA(WR_C);
}

void ORAD(void)
{
    ORA(WR_D);
}

void ORAE(void)
{
    ORA(WR_E);
}

void ORAH(void)
{
    ORA(WR_H);
}

void ORAL(void)
{
    ORA(WR_L);
}

void ORAM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);
    RegFile_WriteReg(WR_A, A | m);
}

void ORAA(void)
{
    ORA(WR_A);
}

void CMPB(void)
{
    CMP(WR_B);
}

void CMPC(void)
{
    CMP(WR_C);
}

void CMPD(void)
{
    CMP(WR_D);
}

void CMPE(void)
{
    CMP(WR_E);
}

void CMPH(void)
{
    CMP(WR_H);
}

void CMPL(void)
{
    CMP(WR_L);
}

void CMPM(void)
{
    uint8_t HL = RegFile_ReadRegPair(RP_HL);
    uint8_t m = Bus_ReadMemory(HL);
    uint8_t A = RegFile_ReadReg(WR_A);

    uint16_t result = A - m;
}

void CMPA(void)
{
    CMP(WR_A);
}

void RNZ(void)
{
    RET_IF(ZERO, false);
}

void POPB(void)
{
    POP(RP_BC);
}

void JNZ(void)
{
    JMP_IF(ZERO, false);
}

void CNZ(void)
{
    CALL_IF(ZERO, false);
}

void PUSHB(void)
{
    PUSH(RP_BC);
}

void ADI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A + d8;
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void RZ(void)
{
    RET_IF(ZERO, true);
}

void JZ(void)
{
    JMP_IF(ZERO, true);
}

void CZ(void)
{
    CALL_IF(ZERO, true);
}

void ACI(void)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A + d8 + carry;
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void RNC(void)
{
    RET_IF(CARRY, false);
}

void POPD(void)
{
    POP(RP_DE);
}

void JNC(void)
{
    JMP_IF(CARRY, false);
}

void OUT(void)
{
    uint8_t port = Bus_ReadMemory(g_cpu.PC++);
    Bus_WritePort((IoPort)port, RegFile_ReadReg(WR_A));
}

void CNC(void)
{
    CALL_IF(CARRY, false);
}

void PUSHD(void)
{
    PUSH(RP_DE);
}

void SUI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A - d8;
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void RC(void)
{
    RET_IF(CARRY, true);
}

void JC(void)
{
    JMP_IF(CARRY, true);
}

void IN(void)
{
    uint8_t port = Bus_ReadMemory(g_cpu.PC++);
    RegFile_WriteReg(WR_A, Bus_ReadPort((IoPort)port));
}

void CC(void)
{
    CALL_IF(CARRY, true);
}

void SBI(void)
{
    uint8_t carry = RegFile_ReadReg(WR_F) & (1 << CARRY) ? 1 : 0;
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A - d8 - carry;
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void RPO(void) {}

void POPH(void)
{
    POP(RP_HL);
}

void JPO(void)
{
}

void XTHL(void)
{
    uint8_t H = RegFile_ReadReg(WR_H);
    uint8_t L = RegFile_ReadReg(WR_L);

    RegFile_WriteReg(WR_L, Bus_ReadMemory(g_cpu.SP));
    RegFile_WriteReg(WR_H, Bus_ReadMemory(g_cpu.SP + 1));

    Bus_WriteMemory(g_cpu.SP, L);
    Bus_WriteMemory(g_cpu.SP + 1, H);
}

void CPO(void) {}

void PUSHH(void)
{
    PUSH(RP_HL);
}

void ANI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A & d8;
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void RPE(void) {}

void PCHL(void)
{
    g_cpu.PC = RegFile_ReadRegPair(RP_HL);
}

void JPE(void) {}

void XCHG(void)
{
    uint16_t HL = RegFile_ReadRegPair(RP_HL);
    uint16_t DE = RegFile_ReadRegPair(RP_DE);

    RegFile_WriteRegPair16(RP_HL, DE);
    RegFile_WriteRegPair16(RP_DE, HL);
}

void CPE(void) {}

void XRI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A ^ d8;
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void RP(void)
{
    RET_IF(SIGN, false);
}

void POPPSW(void)
{
    POP(RP_PSW);
}

void JP(void)
{
    JMP_IF(SIGN, false);
}

void DI(void)
{
    g_cpu.interrupts_enabled = false;
}

void CP(void)
{
    CALL_IF(SIGN, false);
}

void PUSHPSW(void)
{
    PUSH(RP_PSW);
}

void ORI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    uint16_t result = A | d8;
    CPU_AlterZSPCYAC(result);
    RegFile_WriteReg(WR_A, result);
}

void RM(void)
{
    RET_IF(SIGN, true);
}

void SPHL(void)
{
    g_cpu.SP = RegFile_ReadRegPair(RP_HL);
}

void JM(void)
{
    JMP_IF(SIGN, true);
}

void EI(void)
{
    g_cpu.interrupts_enabled = true;
}

void CM(void)
{
    CALL_IF(SIGN, true);
}

void CPI(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    uint8_t A = RegFile_ReadReg(WR_A);
    CPU_AlterZSPCYAC(A - d8);
}
