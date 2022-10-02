#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>

void CPU_Instruction_ADC(uint16_t src);
void CPU_Instruction_AND(uint16_t src);
void CPU_Instruction_ASL(uint16_t src);
void CPU_Instruction_BCC(uint16_t src);
void CPU_Instruction_BCS(uint16_t src);
void CPU_Instruction_BEQ(uint16_t src);
void CPU_Instruction_BIT(uint16_t src);
void CPU_Instruction_BMI(uint16_t src);
void CPU_Instruction_BNE(uint16_t src);
void CPU_Instruction_BPL(uint16_t src);
void CPU_Instruction_BRK(uint16_t src);
void CPU_Instruction_BVC(uint16_t src);
void CPU_Instruction_BVS(uint16_t src);
void CPU_Instruction_CLC(uint16_t src);
void CPU_Instruction_CLD(uint16_t src);
void CPU_Instruction_CLI(uint16_t src);
void CPU_Instruction_CLV(uint16_t src);
void CPU_Instruction_CMP(uint16_t src);
void CPU_Instruction_CPX(uint16_t src);
void CPU_Instruction_CPY(uint16_t src);
void CPU_Instruction_DEC(uint16_t src);
void CPU_Instruction_DEX(uint16_t src);
void CPU_Instruction_DEY(uint16_t src);
void CPU_Instruction_EOR(uint16_t src);
void CPU_Instruction_INC(uint16_t src);
void CPU_Instruction_INX(uint16_t src);
void CPU_Instruction_INY(uint16_t src);
void CPU_Instruction_JMP(uint16_t src);
void CPU_Instruction_JSR(uint16_t src);
void CPU_Instruction_LDA(uint16_t src);
void CPU_Instruction_LDX(uint16_t src);
void CPU_Instruction_LDY(uint16_t src);
void CPU_Instruction_LSR(uint16_t src);
void CPU_Instruction_NOP(uint16_t src);
void CPU_Instruction_ORA(uint16_t src);
void CPU_Instruction_PHA(uint16_t src);
void CPU_Instruction_PHP(uint16_t src);
void CPU_Instruction_PLA(uint16_t src);
void CPU_Instruction_PLP(uint16_t src);
void CPU_Instruction_ROL(uint16_t src);
void CPU_Instruction_ROR(uint16_t src);
void CPU_Instruction_RTI(uint16_t src);
void CPU_Instruction_RTS(uint16_t src);
void CPU_Instruction_SBC(uint16_t src);
void CPU_Instruction_SEC(uint16_t src);
void CPU_Instruction_SED(uint16_t src);
void CPU_Instruction_SEI(uint16_t src);
void CPU_Instruction_STA(uint16_t src);
void CPU_Instruction_STX(uint16_t src);
void CPU_Instruction_STY(uint16_t src);
void CPU_Instruction_TAX(uint16_t src);
void CPU_Instruction_TAY(uint16_t src);
void CPU_Instruction_TSX(uint16_t src);
void CPU_Instruction_TXA(uint16_t src);
void CPU_Instruction_TXS(uint16_t src);
void CPU_Instruction_TYA(uint16_t src);
void CPU_Instruction_ASL_ACC(uint16_t src);
void CPU_Instruction_LSR_ACC(uint16_t src);
void CPU_Instruction_ROL_ACC(uint16_t src);
void CPU_Instruction_ROR_ACC(uint16_t src);

#endif