#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "memory.h"
#include "miniaudio.h"

#define CPUDIAG 0

#define INP1 1
#define INP2_OR_SHFTAMNT 2
#define SHFT_IN 3
#define SHFT_DATA 4
#define SOUND1 3
#define SOUND2 5
#define NO_PORT 8

typedef struct
{
    uint8_t out;
    uint8_t in;
} Port;

typedef struct
{
    Memory *rom;
    Memory *ram;
    Memory *vram;
    uint16_t shiftReg;
    ma_engine audioEngine;
    Port port[NO_PORT];
} Bus;

extern Bus g_bus;

void Bus_Init(void);
void Bus_Destroy(void);

uint8_t Bus_ReadPort(uint8_t portNum);
void Bus_WritePort(uint8_t portNum, uint8_t data);
void Bus_SetInputPort(uint8_t portNum, uint8_t data);

uint8_t Bus_ReadMemory(uint16_t addr);
void Bus_WriteMemory(uint16_t addr, uint8_t data);

#endif // BUS_H