#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include "register_file.h"

typedef enum
{
    SIGN = 7,
    ZERO = 6,
    AUX = 4,
    PARITY = 2,
    CARRY = 0,
} CPU_Flag;

typedef struct
{
    uint8_t cycles_min;
    uint8_t cycles_max;
    void (*execute)(void);

} Instruction;

typedef struct
{
    uint16_t PC;
    uint16_t SP;
    Instruction instruction_table[256];
    bool interrupts_enabled;

} CPU;

extern CPU g_cpu;

void CPU_Init(void);
void CPU_CreateInstructionTable(void);

void CPU_AlterCY(uint16_t testVal);
void CPU_AlterZSPAC(uint16_t testVal);
void CPU_AlterZSPCYAC(uint16_t testVal);

// Common
void LXI(RegisterPair regPair);
void STAX(RegisterPair regPair);
void INX(RegisterPair regPair);
void INR(WorkRegister reg);
void DCR(WorkRegister reg);
void MVI(WorkRegister reg);
void DAD(RegisterPair regPair);
void LDAX(RegisterPair regPair);
void DCX(RegisterPair regPair);
void MOV(WorkRegister dst, WorkRegister src);
void MOVRM(WorkRegister dst);
void MOVMR(WorkRegister src);
void ADD(WorkRegister reg);
void ADC(WorkRegister reg);
void SUB(WorkRegister reg);
void SBB(WorkRegister reg);
void ANA(WorkRegister reg);
void XRA(WorkRegister reg);
void ORA(WorkRegister reg);
void CMP(WorkRegister reg);
void POP(RegisterPair regPair);
void JMP(void);
void PUSH(RegisterPair regPair);
void CALL(void);
void JMP_IF(CPU_Flag flag, bool cond);
void CALL_IF(CPU_Flag flag, bool cond);
void RET_IF(CPU_Flag flag, bool cond);

// Instructions
void NOP(void);
void LXIB(void);
void STAXB(void);
void INXB(void);
void INRB(void);
void DCRB(void);
void MVIB(void);
void RLC(void);
void DADB(void);
void LDAXB(void);
void DCXB(void);
void INRC(void);
void DCRC(void);
void MVIC(void);
void RRC(void);
void LXID(void);
void STAXD(void);
void INXD(void);
void INRD(void);
void DCRD(void);
void MVID(void);
void RAL(void);
void DADD(void);
void LDAXD(void);
void DCXD(void);
void INRE(void);
void DCRE(void);
void MVIE(void);
void RAR(void);
void LXIH(void);
void SHLD(void);
void INXH(void);
void INRH(void);
void DCRH(void);
void MVIH(void);
void DAA(void);
void DADH(void);
void LHLD(void);
void DCXH(void);
void INRL(void);
void DCRL(void);
void MVIL(void);
void CMA(void);
void LXISP(void);
void STA(void);
void INXSP(void);
void INRM(void);
void DCRM(void);
void MVIM(void);
void STC(void);
void DADSP(void);
void LDA(void);
void DCXSP(void);
void INRA(void);
void DCRA(void);
void MVIA(void);
void CMC(void);
void MOVBB(void);
void MOVBC(void);
void MOVBD(void);
void MOVBE(void);
void MOVBH(void);
void MOVBL(void);
void MOVBM(void);
void MOVBA(void);
void MOVCB(void);
void MOVCC(void);
void MOVCD(void);
void MOVCE(void);
void MOVCH(void);
void MOVCL(void);
void MOVCM(void);
void MOVCA(void);
void MOVDB(void);
void MOVDC(void);
void MOVDD(void);
void MOVDE(void);
void MOVDH(void);
void MOVDL(void);
void MOVDM(void);
void MOVDA(void);
void MOVEB(void);
void MOVEC(void);
void MOVED(void);
void MOVEE(void);
void MOVEH(void);
void MOVEL(void);
void MOVEM(void);
void MOVEA(void);
void MOVHB(void);
void MOVHC(void);
void MOVHD(void);
void MOVHE(void);
void MOVHH(void);
void MOVHL(void);
void MOVHM(void);
void MOVHA(void);
void MOVLB(void);
void MOVLC(void);
void MOVLD(void);
void MOVLE(void);
void MOVLH(void);
void MOVLL(void);
void MOVLM(void);
void MOVLA(void);
void MOVMB(void);
void MOVMC(void);
void MOVMD(void);
void MOVME(void);
void MOVMH(void);
void MOVML(void);
void HLT(void);
void MOVMA(void);
void MOVAB(void);
void MOVAC(void);
void MOVAD(void);
void MOVAE(void);
void MOVAH(void);
void MOVAL(void);
void MOVAM(void);
void MOVAA(void);
void ADDB(void);
void ADDC(void);
void ADDD(void);
void ADDE(void);
void ADDH(void);
void ADDL(void);
void ADDM(void);
void ADDA(void);
void ADCB(void);
void ADCC(void);
void ADCD(void);
void ADCE(void);
void ADCH(void);
void ADCL(void);
void ADCM(void);
void ADCA(void);
void SUBB(void);
void SUBC(void);
void SUBD(void);
void SUBE(void);
void SUBH(void);
void SUBL(void);
void SUBM(void);
void SUBA(void);
void SBBB(void);
void SBBC(void);
void SBBD(void);
void SBBE(void);
void SBBH(void);
void SBBL(void);
void SBBM(void);
void SBBA(void);
void ANAB(void);
void ANAC(void);
void ANAD(void);
void ANAE(void);
void ANAH(void);
void ANAL(void);
void ANAM(void);
void ANAA(void);
void XRAB(void);
void XRAC(void);
void XRAD(void);
void XRAE(void);
void XRAH(void);
void XRAL(void);
void XRAM(void);
void XRAA(void);
void ORAB(void);
void ORAC(void);
void ORAD(void);
void ORAE(void);
void ORAH(void);
void ORAL(void);
void ORAM(void);
void ORAA(void);
void CMPB(void);
void CMPC(void);
void CMPD(void);
void CMPE(void);
void CMPH(void);
void CMPL(void);
void CMPM(void);
void CMPA(void);
void RNZ(void);
void POPB(void);
void JNZ(void);
void JMP(void);
void CNZ(void);
void PUSHB(void);
void ADI(void);
// void RST0(void);
void RZ(void);
void RET(void);
void JZ(void);
void CZ(void);
void CALL(void);
void ACI(void);
// void RST1(void);
void RNC(void);
void POPD(void);
void JNC(void);
void OUT(void);
void CNC(void);
void PUSHD(void);
void SUI(void);
// void RST2(void);
void RC(void);
void JC(void);
void IN(void);
void CC(void);
void SBI(void);
// void RST3(void);
void RPO(void);
void POPH(void);
void JPO(void);
void XTHL(void);
void CPO(void);
void PUSHH(void);
void ANI(void);
// void RST4(void);
void RPE(void);
void PCHL(void);
void JPE(void);
void XCHG(void);
void CPE(void);
void XRI(void);
// void RST5(void);
void RP(void);
void POPPSW(void);
void JP(void);
void DI(void);
void CP(void);
void PUSHPSW(void);
void ORI(void);
// void RST6(void);
void RM(void);
void SPHL(void);
void JM(void);
void EI(void);
void CM(void);
void CPI(void);
// void RST7(void);

#endif // CPU_H