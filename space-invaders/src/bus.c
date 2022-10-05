#include "bus.h"
#include <stdio.h>

Bus g_bus;

void Bus_Init(void)
{
    g_bus.rom = Memory_Create(13);
    g_bus.ram = Memory_Create(10);
    g_bus.vram = Memory_Create(13);

    Memory_LoadFromFile(g_bus.rom, 0x0000, "../rom/invaders.h");
    Memory_LoadFromFile(g_bus.rom, 0x0800, "../rom/invaders.g");
    Memory_LoadFromFile(g_bus.rom, 0x1000, "../rom/invaders.f");
    Memory_LoadFromFile(g_bus.rom, 0x1800, "../rom/invaders.e");
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
        return g_bus.shift_register >> (8 - g_bus.io_ports[INP2_OR_SHFTAMNT]);
    default:
        return g_bus.io_ports[port];
    }

    return 0;
}

void Bus_WritePort(IoPort port, uint8_t data)
{
    switch (port)
    {
    case INP2_OR_SHFTAMNT:
        g_bus.io_ports[port] = data & 0x07;
        break;
    case SOUND1:
    case SOUND2:
        g_bus.io_ports[port] = data;
        break;
    case SHFT_DATA:
        g_bus.shift_register = (g_bus.shift_register >> 8) | (data << 8);
        break;
    default:
        break;
    }
}

uint8_t Bus_ReadMemory(uint16_t addr)
{
    if (addr >= 0x0000 && addr <= 0x2000)
    {
        return Memory_Read(g_bus.rom, addr);
    }

    if (addr >= 0x2400 && addr <= 0x4000)
    {
        return Memory_Read(g_bus.vram, addr);
    }

    return Memory_Read(g_bus.ram, addr);
}

void Bus_WriteMemory(uint16_t addr, uint8_t data)
{
    if (addr >= 0x2400 && addr <= 0x3FFF)
    {
        Memory_Write(g_bus.vram, addr, data);
    }
    else
    {
        Memory_Write(g_bus.ram, addr, data);
    }
}
