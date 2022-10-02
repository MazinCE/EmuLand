#ifndef C64BUS_H
#define C64BUS_H

#include "CPU/cpu.h"
#include "VIC/vic.h"
#include "Memory/Memory.h"
#include "CIA/CIA.h"

typedef enum
{
    KERNAL = 0x01,
    CHARACTER = 0x02,
    BASIC = 0x04,
    IO = 0x08,

} C64BusDeviceType;

typedef enum
{
    CPU_PORT = 0,
    CIA_ONE_PRA,
    CIA_ONE_PRB,
    CIA_TWO_PRA,
    CIA_TWO_PRB,

} C64BusPortType;

typedef enum
{
    INTERRUPT_IRQ = 0,
    INTERRUPT_NMI,
    INTERRUPT_RST,

} C64BusInterruptType;

typedef struct C64Bus C64Bus;

extern C64Bus g_C64Bus;

void C64Bus_Init();
void C64Bus_Destroy();

void C64Bus_Tick();

uint8_t C64Bus_ReadPort(C64BusPortType portType);
void C64Bus_WritePort(C64BusPortType portType, uint8_t data);

void C64Bus_SetRDY(bool val);
void C64Bus_SetAEC(bool val);
bool C64Bus_GetRDY();
bool C64Bus_GetAEC();

void C64Bus_Release();

uint8_t C64Bus_GetVicMemoryBank();
uint16_t C64Bus_VicRead(uint16_t addr);
uint32_t *C64Bus_GetVicVideoFrame();

Memory* C64Bus_GetRAM();

void C64Bus_CpuInterrupt(C64BusInterruptType interruptType);

uint8_t C64Bus_CpuRead(uint16_t addr);
void C64Bus_CpuWrite(uint16_t addr, uint8_t data);

void C64Bus_SetCpuAccessRange();
bool C64Bus_CpuCanAccess();
bool C64Bus_InCpuAccessRange(C64BusDeviceType type,
                             uint16_t addr,
                             uint16_t base,
                             uint16_t limit);

#endif