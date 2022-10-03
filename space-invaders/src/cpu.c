#include "cpu.h"
#include "register_file.h"
#include "bus.h"

void CPU_Init(void) {}
void CPU_CreateInstructionTable(void) {}

void NOP(void)
{
}

void LXIB(void)
{
    uint8_t B = Bus_ReadMemory(g_cpu.PC++);
    uint8_t C = Bus_ReadMemory(g_cpu.PC++);

    RegisterFile_WriteRegisterPair8(RP_BC, B, C);
}

void STAXB(void)
{
    uint16_t BC = RegisterFile_ReadRegisterPair(RP_BC);
    uint8_t A = RegisterFile_ReadRegister(WR_A);

    Bus_WriteMemory(BC, A);
}

void INXB(void)
{
    uint16_t BC = RegisterFile_ReadRegisterPair(RP_BC);
    RegisterFile_WriteRegisterPair16(RP_BC, BC + 1);
}

void INRB(void)
{
    uint8_t B = RegisterFile_ReadRegister(WR_B);
    RegisterFile_WriteRegister(WR_B, B + 1);
}

void DCRB(void)
{
    uint8_t B = RegisterFile_ReadRegister(WR_B);
    RegisterFile_WriteRegister(WR_B, B + 1);
}

void MVIB(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    RegisterFile_WriteRegister(WR_B, d8);
}

void RLC(void) {}

void DADB(void)
{
    uint16_t BC = RegisterFile_ReadRegisterPair(RP_BC);
    uint16_t HL = RegisterFile_ReadRegisterPair(RP_HL);

    RegisterFile_WriteRegisterPair16(RP_HL, HL + BC);
}

void LDAXB(void)
{
    uint16_t BC = RegisterFile_ReadRegisterPair(RP_BC);
    uint8_t d8 = Bus_ReadMemory(BC);
    RegisterFile_WriteRegister(WR_A, d8);
}

void DCXB(void)
{
    uint16_t BC = RegisterFile_ReadRegisterPair(RP_BC);
    RegisterFile_WriteRegisterPair16(RP_BC, BC - 1);
}

void INRC(void)
{
    uint8_t C = RegisterFile_ReadRegister(WR_C);
    RegisterFile_WriteRegister(WR_C, C + 1);
}

void DCRC(void)
{
    uint8_t C = RegisterFile_ReadRegister(WR_C);
    RegisterFile_WriteRegister(WR_C, C - 1);
}

void MVIC(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    RegisterFile_WriteRegister(WR_C, d8);
}

void RRC(void) {}

void LXID(void)
{
    uint8_t D = Bus_ReadMemory(g_cpu.PC++);
    uint8_t E = Bus_ReadMemory(g_cpu.PC++);

    RegisterFile_WriteRegisterPair8(RP_DE, D, E);
}

void STAXD(void)
{
    uint16_t DE = RegisterFile_ReadRegisterPair(RP_DE);
    uint8_t A = RegisterFile_ReadRegister(WR_A);

    Bus_WriteMemory(DE, A);
}

void INXD(void)
{
    uint16_t DE = RegisterFile_ReadRegisterPair(RP_DE);
    RegisterFile_WriteRegisterPair16(RP_DE, DE + 1);
}

void INRD(void)
{
    uint8_t D = RegisterFile_ReadRegister(WR_D);
    RegisterFile_WriteRegister(WR_D, D + 1);
}

void DCRD(void)
{
    uint8_t D = RegisterFile_ReadRegister(WR_D);
    RegisterFile_WriteRegister(WR_D, D - 1);
}

void MVID(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    RegisterFile_WriteRegister(WR_D, d8);
}

void RAL(void) {}

void DADD(void)
{
    uint16_t DE = RegisterFile_ReadRegisterPair(RP_DE);
    uint16_t HL = RegisterFile_ReadRegisterPair(RP_HL);

    RegisterFile_WriteRegisterPair16(RP_HL, HL + DE);
}

void LDAXD(void)
{
    uint16_t DE = RegisterFile_ReadRegisterPair(RP_DE);
    uint8_t d8 = Bus_ReadMemory(DE);
    RegisterFile_WriteRegister(WR_A, d8);
}

void DCXD(void)
{
    uint16_t DE = RegisterFile_ReadRegisterPair(RP_DE);
    RegisterFile_WriteRegisterPair16(RP_DE, DE - 1);
}

void INRE(void)
{
    uint8_t E = RegisterFile_ReadRegister(WR_E);
    RegisterFile_WriteRegister(WR_E, E + 1);
}

void DCRE(void)
{
    uint8_t E = RegisterFile_ReadRegister(WR_E);
    RegisterFile_WriteRegister(WR_E, E - 1);
}

void MVIE(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    RegisterFile_WriteRegister(WR_E, d8);
}

void RAR(void) {}

void LXIH(void)
{
    uint8_t H = Bus_ReadMemory(g_cpu.PC++);
    uint8_t L = Bus_ReadMemory(g_cpu.PC++);

    RegisterFile_WriteRegisterPair8(RP_HL, H, L);
}

void SHLD(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    uint16_t addr = (addr_hi << 8) | addr_lo;

    uint8_t H = RegisterFile_ReadRegister(WR_H);
    uint8_t L = RegisterFile_ReadRegister(WR_L);

    Bus_WriteMemory(addr, L);
    Bus_WriteMemory(addr + 1, H);
}

void INXH(void)
{
    uint16_t HL = RegisterFile_ReadRegisterPair(RP_HL);
    RegisterFile_WriteRegister(RP_HL, HL + 1);
}

void INRH(void)
{
    uint8_t H = RegisterFile_ReadRegister(WR_H);
    RegisterFile_WriteRegister(WR_H, H + 1);
}

void DCRH(void)
{
    uint8_t H = RegisterFile_ReadRegister(WR_H);
    RegisterFile_WriteRegister(WR_H, H - 1);
}

void MVIH(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    RegisterFile_WriteRegister(WR_H, d8);
}

void DAA(void) {}

void DADH(void)
{
    uint16_t HL = RegisterFile_ReadRegisterPair(RP_HL);
    RegisterFile_WriteRegister(RP_HL, HL + HL);
}

void LHLD(void)
{
    uint8_t addr_lo = Bus_ReadMemory(g_cpu.PC++);
    uint8_t addr_hi = Bus_ReadMemory(g_cpu.PC++);

    uint16_t addr = (addr_hi << 8) | addr_lo;

    RegisterFile_WriteRegister(WR_L, Bus_ReadMemory(addr));
    RegisterFile_WriteRegister(WR_H, Bus_ReadMemory(addr + 1));
}

void DCXH(void)
{
    uint16_t HL = RegisterFile_ReadRegisterPair(RP_HL);
    RegisterFile_WriteRegister(RP_HL, HL - 1);
}

void INRL(void)
{
    uint8_t L = RegisterFile_ReadRegister(WR_L);
    RegisterFile_WriteRegister(WR_L, L + 1);
}

void DCRL(void)
{
    uint8_t L = RegisterFile_ReadRegister(WR_L);
    RegisterFile_WriteRegister(WR_L, L - 1);
}

void MVIL(void)
{
    uint8_t d8 = Bus_ReadMemory(g_cpu.PC++);
    RegisterFile_WriteRegister(WR_L, d8);
}

void CMA(void)
{
    uint8_t A = RegisterFile_ReadRegister(WR_A);
    RegisterFile_WriteRegister(WR_A, ~A);
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
    uint8_t A = RegisterFile_ReadRegister(WR_A);

    Bus_WriteMemory(addr, A);
}

void INXSP(void) 
{
    g_cpu.SP++;
}

void INRM(void) {}
void DCRM(void) {}
void MVIM(void) {}
void STC(void) {}
void DADSP(void) {}
void LDA(void) {}
void DCXSP(void) {}
void INRA(void) {}
void DCRA(void) {}
void MVIA(void) {}
void CMC(void) {}
void MOVBB(void) {}
void MOVBC(void) {}
void MOVBD(void) {}
void MOVBE(void) {}
void MOVBH(void) {}
void MOVBL(void) {}
void MOVBM(void) {}
void MOVBA(void) {}
void MOVCB(void) {}
void MOVCC(void) {}
void MOVCD(void) {}
void MOVCE(void) {}
void MOVCH(void) {}
void MOVCL(void) {}
void MOVCM(void) {}
void MOVCA(void) {}
void MOVDB(void) {}
void MOVDC(void) {}
void MOVDD(void) {}
void MOVDE(void) {}
void MOVDH(void) {}
void MOVDL(void) {}
void MOVDM(void) {}
void MOVDA(void) {}
void MOVEB(void) {}
void MOVEC(void) {}
void MOVED(void) {}
void MOVEE(void) {}
void MOVEH(void) {}
void MOVEL(void) {}
void MOVEM(void) {}
void MOVEA(void) {}
void MOVHB(void) {}
void MOVHC(void) {}
void MOVHD(void) {}
void MOVHE(void) {}
void MOVHH(void) {}
void MOVHL(void) {}
void MOVHM(void) {}
void MOVHA(void) {}
void MOVLB(void) {}
void MOVLC(void) {}
void MOVLD(void) {}
void MOVLE(void) {}
void MOVLH(void) {}
void MOVLL(void) {}
void MOVLM(void) {}
void MOVLA(void) {}
void MOVMB(void) {}
void MOVMC(void) {}
void MOVMD(void) {}
void MOVME(void) {}
void MOVMH(void) {}
void MOVML(void) {}
void HLT(void) {}
void MOVMA(void) {}
void MOVAB(void) {}
void MOVAC(void) {}
void MOVAD(void) {}
void MOVAE(void) {}
void MOVAH(void) {}
void MOVAL(void) {}
void MOVAM(void) {}
void MOVAA(void) {}
void ADDB(void) {}
void ADDC(void) {}
void ADDD(void) {}
void ADDE(void) {}
void ADDH(void) {}
void ADDL(void) {}
void ADDM(void) {}
void ADDA(void) {}
void ADCB(void) {}
void ADCC(void) {}
void ADCD(void) {}
void ADCE(void) {}
void ADCH(void) {}
void ADCL(void) {}
void ADCM(void) {}
void ADCA(void) {}
void SUBB(void) {}
void SUBC(void) {}
void SUBD(void) {}
void SUBE(void) {}
void SUBH(void) {}
void SUBL(void) {}
void SUBM(void) {}
void SUBA(void) {}
void SBBB(void) {}
void SBBC(void) {}
void SBBD(void) {}
void SBBE(void) {}
void SBBH(void) {}
void SBBL(void) {}
void SBBM(void) {}
void SBBA(void) {}
void ANAB(void) {}
void ANAC(void) {}
void ANAD(void) {}
void ANAE(void) {}
void ANAH(void) {}
void ANAL(void) {}
void ANAM(void) {}
void ANAA(void) {}
void XRAB(void) {}
void XRAC(void) {}
void XRAD(void) {}
void XRAE(void) {}
void XRAH(void) {}
void XRAL(void) {}
void XRAM(void) {}
void XRAA(void) {}
void ORAB(void) {}
void ORAC(void) {}
void ORAD(void) {}
void ORAE(void) {}
void ORAH(void) {}
void ORAL(void) {}
void ORAM(void) {}
void ORAA(void) {}
void CMPB(void) {}
void CMPC(void) {}
void CMPD(void) {}
void CMPE(void) {}
void CMPH(void) {}
void CMPL(void) {}
void CMPM(void) {}
void CMPA(void) {}
void RNZ(void) {}
void POPB(void) {}
void JNZ(void) {}
void JMP(void) {}
void CNZ(void) {}
void PUSHB(void) {}
void ADI(void) {}
// void RST0(void){}
void RZ(void) {}
void RET(void) {}
void JZ(void) {}
void CZ(void) {}
void CALL(void) {}
void ACI(void) {}
// void RST1(void){}
void RNC(void) {}
void POPD(void) {}
void JNC(void) {}
void OUT(void) {}
void CNC(void) {}
void PUSHD(void) {}
void SUI(void) {}
// void RST2(void){}
void RC(void) {}
void JC(void) {}
void IN(void) {}
void CC(void) {}
void SBI(void) {}
// void RST3(void){}
void RPO(void) {}
void POPH(void) {}
void JPO(void) {}
void XTHL(void) {}
void CPO(void) {}
void PUSHH(void) {}
void ANI(void) {}
// void RST4(void){}
void RPE(void) {}
void PCHL(void) {}
void JPE(void) {}
void XCHG(void) {}
void CPE(void) {}
void XRI(void) {}
// void RST5(void){}
void RP(void) {}
void POPPSW(void) {}
void JP(void) {}
void DI(void) {}
void CP(void) {}
void PUSHPSW(void) {}
void ORI(void) {}
// void RST6(void){}
void RM(void) {}
void SPHL(void) {}
void JM(void) {}
void EI(void) {}
void CM(void) {}
void CPI(void) {}
// void RST7(void){}