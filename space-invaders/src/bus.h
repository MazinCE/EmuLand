#ifndef BUS_H
#define BUS_H

#include <stdint.h>
#include "memory.h"

typedef enum
{
    INP0 = 0,
    INP1,
    INP2_OR_SHFTAMNT,
    SHFT_IN,
    SOUND1,
    SHFT_DATA,
    SOUND2,
    MAX_PORTS,

} IoPort;

typedef struct
{
    Memory *rom;
    Memory *ram;
    Memory *vram;
    uint16_t shift_register;
    uint8_t io_ports[MAX_PORTS];

} Bus;

void Bus_Init(void);
void Bus_Destroy(void);

uint8_t Bus_ReadPort(IoPort port);
void Bus_WritePort(IoPort port, uint8_t data);

uint8_t Bus_ReadMemory(uint16_t addr);
void Bus_WriteMemory(uint16_t addr, uint8_t data);

#endif // BUS_H