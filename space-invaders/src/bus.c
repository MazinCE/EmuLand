#include "bus.h"
#include <stdio.h>

Bus g_bus;

void Bus_Init(void)
{
    g_bus.ram = Memory_Create(11);

#if CPUDIAG
    Memory_LoadFromFile(g_bus.ram, 0x0100, "../rom/cpudiag.bin");
    // Memory_Write(g_bus.ram, 368, 0x07);

    // Skip DAA test
    Memory_Write(g_bus.ram, 0x59c, 0xc3); // JMP
    Memory_Write(g_bus.ram, 0x59d, 0xc2);
    Memory_Write(g_bus.ram, 0x59e, 0x05);

    // uint8_t prog[] = {
    //     0x11,
    //     0x0E,
    //     0x00,
    //     0x21,
    //     0x13,
    //     0x00,
    //     0x06,
    //     0x00,
    //     0x0E,
    //     0x05,
    //     0xCD,
    //     0x1D,
    //     0x00,
    //     0x76,
    //     0x11,
    //     0x22,
    //     0x33,
    //     0x44,
    //     0x55,
    //     0x11,
    //     0x22,
    //     0x33,
    //     0x44,
    //     0x55,
    //     0x00,
    //     0x00,
    //     0x00,
    //     0x00,
    //     0x00,
    //     0x78,
    //     0xB1,
    //     0xC8,
    //     0x1A,
    //     0x77,
    //     0x13,
    //     0x23,
    //     0x0B,
    //     0x78,
    //     0xB1,
    //     0xC2,
    //     0x20,
    //     0x00,
    //     0xC9,
    // };

    // for (int i = 0; i < sizeof(prog); ++i)
    // {
    //     Memory_Write(g_bus.ram, i, prog[i]);
    // }

#else
    g_bus.rom = Memory_Create(13);
    g_bus.vram = Memory_Create(13);

    Memory_LoadFromFile(g_bus.rom, 0x0000, "../rom/invaders.h");
    Memory_LoadFromFile(g_bus.rom, 0x0800, "../rom/invaders.g");
    Memory_LoadFromFile(g_bus.rom, 0x1000, "../rom/invaders.f");
    Memory_LoadFromFile(g_bus.rom, 0x1800, "../rom/invaders.e");
#endif
}

void Bus_Destroy(void)
{
    Memory_Destroy(g_bus.rom);
    Memory_Destroy(g_bus.ram);
    Memory_Destroy(g_bus.vram);
}

uint8_t Bus_ReadPort(IoPort port)
{
    switch (port)
    {
    case SHFT_IN:
        return g_bus.shiftReg >> (8 - (g_bus.ioPorts[INP2_OR_SHFTAMNT] & 0x07));
    default:
        return g_bus.ioPorts[port];
    }

    return 0;
}

void Bus_WritePort(IoPort port, uint8_t data)
{
    switch (port)
    {
    case INP2_OR_SHFTAMNT:
    case SOUND1:
    case SOUND2:
        g_bus.ioPorts[port] = data;
        break;
    case SHFT_DATA:
        g_bus.shiftReg = (g_bus.shiftReg >> 8) | (data << 8);
        break;
    default:
        break;
    }
}

uint8_t Bus_ReadMemory(uint16_t addr)
{
#if CPUDIAG == 0
    if (addr <= 0x2000)
    {
        return Memory_Read(g_bus.rom, addr);
    }

    if (addr >= 0x2400 && addr <= 0x3FFF)
    {
        return Memory_Read(g_bus.vram, addr);
    }
#endif

    return Memory_Read(g_bus.ram, addr);
}

void Bus_WriteMemory(uint16_t addr, uint8_t data)
{
#if CPUDIAG == 0
    if (addr >= 0x2400 && addr <= 0x3FFF)
    {
        Memory_Write(g_bus.vram, addr, data);
    }
    else
#endif
    {
        Memory_Write(g_bus.ram, addr, data);
    }
}
