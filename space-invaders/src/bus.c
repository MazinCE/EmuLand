#include "bus.h"
#include "sound.h"

Bus g_bus;

void Bus_Init(void)
{
    g_bus.ram = Memory_Create(10);

#if CPUDIAG
    Memory_LoadFromFile(g_bus.ram, 0x0100, "../rom/cpudiag.bin");
    // Memory_Write(g_bus.ram, 368, 0x07);

    // Skip DAA test
    Memory_Write(g_bus.ram, 0x59c, 0xc3); // JMP
    Memory_Write(g_bus.ram, 0x59d, 0xc2);
    Memory_Write(g_bus.ram, 0x59e, 0x05);
#else
    g_bus.rom = Memory_Create(13);
    g_bus.vram = Memory_Create(13);

    Memory_LoadFromFile(g_bus.rom, 0x0000, "../rom/invaders.h");
    Memory_LoadFromFile(g_bus.rom, 0x0800, "../rom/invaders.g");
    Memory_LoadFromFile(g_bus.rom, 0x1000, "../rom/invaders.f");
    Memory_LoadFromFile(g_bus.rom, 0x1800, "../rom/invaders.e");
#endif

    Sound_Init();
}

void Bus_Destroy(void)
{
    Memory_Destroy(g_bus.rom);
    Memory_Destroy(g_bus.ram);
    Memory_Destroy(g_bus.vram);
    Sound_Destroy();
}

uint8_t Bus_ReadPort(uint8_t portNum)
{
    if (portNum == SHFT_IN)
    {
        return g_bus.shiftReg >> (8 - g_bus.port[INP2_OR_SHFTAMNT].out);
    }

    return g_bus.port[portNum].in;
}

void Bus_WritePort(uint8_t portNum, uint8_t data)
{
    if (portNum == SHFT_DATA)
    {
        g_bus.shiftReg = (g_bus.shiftReg >> 8) | (data << 8);
    }
    else if (portNum == SOUND1 || portNum == SOUND2)
    {
        Sound_Play(portNum, data, g_bus.port[portNum].out);
        g_bus.port[portNum].out = data;
    }
    else
    {
        g_bus.port[portNum].out = data;
    }
}

void Bus_SetInputPort(uint8_t portNum, uint8_t data)
{
    g_bus.port[portNum].in = data;
}

uint8_t Bus_ReadMemory(uint16_t addr)
{
#if CPUDIAG == 0
    if (addr <= 0x1FFF)
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
