#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "memory.h"

#define CPUDIAG 0

typedef enum
{
    INP1 = 1,
    INP2_OR_SHFTAMNT,
    SHFT_IN,
    SHFT_DATA,
    SOUND1,
    SOUND2,
    MAX_PORTS,

} IoPort;

typedef struct
{
    Memory *rom;
    Memory *ram;
    Memory *vram;
    uint16_t shiftReg;
    uint8_t shamt;
    uint8_t ioPorts[MAX_PORTS];

} Bus;

extern Bus g_bus;


void Bus_Init(void);
void Bus_Destroy(void);

uint8_t Bus_ReadPort(IoPort port);
void Bus_WritePort(IoPort port, uint8_t data);

uint8_t Bus_ReadMemory(uint16_t addr);
void Bus_WriteMemory(uint16_t addr, uint8_t data);

#endif // BUS_H