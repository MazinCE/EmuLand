#ifndef CPU_H
#define CPU_H

#include "cpu_defines.h"

typedef struct
{
    CPU_Registers registers;
    CPU_Instruction instructionTable[256];
    CPU_Interrupt pendingInterrupt;
    CPU_State state;
    uint8_t port[2];
    uint8_t cycle;
    uint8_t opCode;
    bool hasExtraCycles;

} CPU;

extern CPU g_cpu;

void CPU_Init(void);
void CPU_Destroy(void);

void CPU_CreateInsructionTable(void);

void CPU_Tick(void);
void CPU_Execute(void);
void CPU_ExecuteInterrupt(void);

bool CPU_IsReadCycle(void);
bool CPU_InstrTypeIsReadModifyWrite(void);

void CPU_SetPendingInterrupt(uint8_t type, void (*interruptFn)(void));
void CPU_TriggerInterrupt(uint8_t type);

void CPU_IRQ(void);
void CPU_NMI(void);
void CPU_RST(void);

bool CPU_TestFlag(CPU_Flag CPU_Flag);
void CPU_SetFlag(CPU_Flag CPU_Flag, bool val);
void CPU_ClearFlag(CPU_Flag CPU_Flag);

uint8_t CPU_GetCarry(void);
uint8_t CPU_GetBorrow(void);

void CPU_PushStack(uint8_t data);
void CPU_PushWordStack(uint16_t data);

uint8_t CPU_PopStack(void);
uint16_t CPU_PopWordStack(void);

void CPU_BranchSet(CPU_Flag CPU_Flag, uint16_t offset);
void CPU_BranchClear(CPU_Flag CPU_Flag, uint16_t offset);

void CPU_Compare(uint8_t reg, uint16_t src);
void CPU_Load(uint8_t *dst, uint16_t src);
void CPU_Move(uint8_t *dst, uint16_t src);
void CPU_ArithmaticShiftLeft(uint8_t *src);
void CPU_LogicalShiftRight(uint8_t *src);

void CPU_Increment(uint8_t *src);
void CPU_Decrement(uint8_t *src);

void CPU_RotateRight(uint8_t *src);
void CPU_RotateLeft(uint8_t *src);

#endif