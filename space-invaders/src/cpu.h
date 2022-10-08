#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include "register_file.h"
#include "bus.h"

typedef enum
{
    CARRY  = 0,
    PARITY = 2,
    AUX    = 4,
    ZERO   = 6,
    SIGN   = 7,

} CPU_Flag;

typedef uint8_t (*InstructionFn)(void);

typedef struct
{
    uint16_t PC;
    uint16_t SP;
    uint32_t cycles;
    InstructionFn instructionTable[256];
    bool interruptsEnabled;

} CPU;

extern CPU g_cpu;

void CPU_Init(void);
void CPU_CreateInstructionTable(void);
uint32_t CPU_Tick(void);
void CPU_ResetTicks(void);
void CPU_Interrupt(uint8_t rst);

void CPU_Diag(void);

void CPU_UpdateFlagCY(uint32_t testVal);
// void CPU_UpdateFlagAC(uint8_t testVal);
void CPU_UpdateFlagZSPAC(uint8_t testVal);
void CPU_UpdateFlagZSPCYAC(uint32_t testVal);

// Common
uint8_t LXI(RegisterPair regPair);
uint8_t STAX(RegisterPair regPair);
uint8_t INX(RegisterPair regPair);
uint8_t INR(WorkRegister reg);
uint8_t DCR(WorkRegister reg);
uint8_t MVI(WorkRegister reg);
uint8_t DAD(RegisterPair regPair);
uint8_t LDAX(RegisterPair regPair);
uint8_t DCX(RegisterPair regPair);
uint8_t MOV(WorkRegister dst, WorkRegister src);
uint8_t MOVRM(WorkRegister dst);
uint8_t MOVMR(WorkRegister src);
uint8_t ADD(WorkRegister reg);
uint8_t ADC(WorkRegister reg);
uint8_t SUB(WorkRegister reg);
uint8_t SBB(WorkRegister reg);
uint8_t ANA(WorkRegister reg);
uint8_t XRA(WorkRegister reg);
uint8_t ORA(WorkRegister reg);
uint8_t CMP(WorkRegister reg);
uint8_t POP(RegisterPair regPair);
uint8_t PUSH(RegisterPair regPair);
uint8_t JMP_IF(CPU_Flag flag, bool cond);
uint8_t CALL_IF(CPU_Flag flag, bool cond);
uint8_t RET_IF(CPU_Flag flag, bool cond);

// Instructions
uint8_t NOP(void);
uint8_t LXIB(void);
uint8_t STAXB(void);
uint8_t INXB(void);
uint8_t INRB(void);
uint8_t DCRB(void);
uint8_t MVIB(void);
uint8_t RLC(void);
uint8_t DADB(void);
uint8_t LDAXB(void);
uint8_t DCXB(void);
uint8_t INRC(void);
uint8_t DCRC(void);
uint8_t MVIC(void);
uint8_t RRC(void);
uint8_t LXID(void);
uint8_t STAXD(void);
uint8_t INXD(void);
uint8_t INRD(void);
uint8_t DCRD(void);
uint8_t MVID(void);
uint8_t RAL(void);
uint8_t DADD(void);
uint8_t LDAXD(void);
uint8_t DCXD(void);
uint8_t INRE(void);
uint8_t DCRE(void);
uint8_t MVIE(void);
uint8_t RAR(void);
uint8_t LXIH(void);
uint8_t SHLD(void);
uint8_t INXH(void);
uint8_t INRH(void);
uint8_t DCRH(void);
uint8_t MVIH(void);
uint8_t DAA(void);
uint8_t DADH(void);
uint8_t LHLD(void);
uint8_t DCXH(void);
uint8_t INRL(void);
uint8_t DCRL(void);
uint8_t MVIL(void);
uint8_t CMA(void);
uint8_t LXISP(void);
uint8_t STA(void);
uint8_t INXSP(void);
uint8_t INRM(void);
uint8_t DCRM(void);
uint8_t MVIM(void);
uint8_t STC(void);
uint8_t DADSP(void);
uint8_t LDA(void);
uint8_t DCXSP(void);
uint8_t INRA(void);
uint8_t DCRA(void);
uint8_t MVIA(void);
uint8_t CMC(void);
uint8_t MOVBB(void);
uint8_t MOVBC(void);
uint8_t MOVBD(void);
uint8_t MOVBE(void);
uint8_t MOVBH(void);
uint8_t MOVBL(void);
uint8_t MOVBM(void);
uint8_t MOVBA(void);
uint8_t MOVCB(void);
uint8_t MOVCC(void);
uint8_t MOVCD(void);
uint8_t MOVCE(void);
uint8_t MOVCH(void);
uint8_t MOVCL(void);
uint8_t MOVCM(void);
uint8_t MOVCA(void);
uint8_t MOVDB(void);
uint8_t MOVDC(void);
uint8_t MOVDD(void);
uint8_t MOVDE(void);
uint8_t MOVDH(void);
uint8_t MOVDL(void);
uint8_t MOVDM(void);
uint8_t MOVDA(void);
uint8_t MOVEB(void);
uint8_t MOVEC(void);
uint8_t MOVED(void);
uint8_t MOVEE(void);
uint8_t MOVEH(void);
uint8_t MOVEL(void);
uint8_t MOVEM(void);
uint8_t MOVEA(void);
uint8_t MOVHB(void);
uint8_t MOVHC(void);
uint8_t MOVHD(void);
uint8_t MOVHE(void);
uint8_t MOVHH(void);
uint8_t MOVHL(void);
uint8_t MOVHM(void);
uint8_t MOVHA(void);
uint8_t MOVLB(void);
uint8_t MOVLC(void);
uint8_t MOVLD(void);
uint8_t MOVLE(void);
uint8_t MOVLH(void);
uint8_t MOVLL(void);
uint8_t MOVLM(void);
uint8_t MOVLA(void);
uint8_t MOVMB(void);
uint8_t MOVMC(void);
uint8_t MOVMD(void);
uint8_t MOVME(void);
uint8_t MOVMH(void);
uint8_t MOVML(void);
uint8_t HLT(void);
uint8_t MOVMA(void);
uint8_t MOVAB(void);
uint8_t MOVAC(void);
uint8_t MOVAD(void);
uint8_t MOVAE(void);
uint8_t MOVAH(void);
uint8_t MOVAL(void);
uint8_t MOVAM(void);
uint8_t MOVAA(void);
uint8_t ADDB(void);
uint8_t ADDC(void);
uint8_t ADDD(void);
uint8_t ADDE(void);
uint8_t ADDH(void);
uint8_t ADDL(void);
uint8_t ADDM(void);
uint8_t ADDA(void);
uint8_t ADCB(void);
uint8_t ADCC(void);
uint8_t ADCD(void);
uint8_t ADCE(void);
uint8_t ADCH(void);
uint8_t ADCL(void);
uint8_t ADCM(void);
uint8_t ADCA(void);
uint8_t SUBB(void);
uint8_t SUBC(void);
uint8_t SUBD(void);
uint8_t SUBE(void);
uint8_t SUBH(void);
uint8_t SUBL(void);
uint8_t SUBM(void);
uint8_t SUBA(void);
uint8_t SBBB(void);
uint8_t SBBC(void);
uint8_t SBBD(void);
uint8_t SBBE(void);
uint8_t SBBH(void);
uint8_t SBBL(void);
uint8_t SBBM(void);
uint8_t SBBA(void);
uint8_t ANAB(void);
uint8_t ANAC(void);
uint8_t ANAD(void);
uint8_t ANAE(void);
uint8_t ANAH(void);
uint8_t ANAL(void);
uint8_t ANAM(void);
uint8_t ANAA(void);
uint8_t XRAB(void);
uint8_t XRAC(void);
uint8_t XRAD(void);
uint8_t XRAE(void);
uint8_t XRAH(void);
uint8_t XRAL(void);
uint8_t XRAM(void);
uint8_t XRAA(void);
uint8_t ORAB(void);
uint8_t ORAC(void);
uint8_t ORAD(void);
uint8_t ORAE(void);
uint8_t ORAH(void);
uint8_t ORAL(void);
uint8_t ORAM(void);
uint8_t ORAA(void);
uint8_t CMPB(void);
uint8_t CMPC(void);
uint8_t CMPD(void);
uint8_t CMPE(void);
uint8_t CMPH(void);
uint8_t CMPL(void);
uint8_t CMPM(void);
uint8_t CMPA(void);
uint8_t RNZ(void);
uint8_t POPB(void);
uint8_t JNZ(void);
uint8_t JMP(void);
uint8_t CNZ(void);
uint8_t PUSHB(void);
uint8_t ADI(void);
uint8_t RZ(void);
uint8_t RET(void);
uint8_t JZ(void);
uint8_t CZ(void);
uint8_t CALL(void);
uint8_t ACI(void);
uint8_t RNC(void);
uint8_t POPD(void);
uint8_t JNC(void);
uint8_t OUT(void);
uint8_t CNC(void);
uint8_t PUSHD(void);
uint8_t SUI(void);
uint8_t RC(void);
uint8_t JC(void);
uint8_t IN(void);
uint8_t CC(void);
uint8_t SBI(void);
uint8_t RPO(void);
uint8_t POPH(void);
uint8_t JPO(void);
uint8_t XTHL(void);
uint8_t CPO(void);
uint8_t PUSHH(void);
uint8_t ANI(void);
uint8_t RPE(void);
uint8_t PCHL(void);
uint8_t JPE(void);
uint8_t XCHG(void);
uint8_t CPE(void);
uint8_t XRI(void);
uint8_t RP(void);
uint8_t POPPSW(void);
uint8_t JP(void);
uint8_t DI(void);
uint8_t CP(void);
uint8_t PUSHPSW(void);
uint8_t ORI(void);
uint8_t RM(void);
uint8_t SPHL(void);
uint8_t JM(void);
uint8_t EI(void);
uint8_t CM(void);
uint8_t CPI(void);

#endif // CPU_H