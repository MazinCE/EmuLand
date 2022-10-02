#include "c64bus.h"
#include <stdlib.h>
#include <stdio.h>

struct C64Bus
{
    Memory *rom[3];
    Memory *ram;
    Memory *color_ram;
    Cia *cia[2];
    uint8_t cpuAccessRange;
    bool rdy;
    bool aec;
};

C64Bus g_C64Bus;

void C64Bus_Init()
{
    C64Bus_Release();

    CPU_Init();
    Vic_Init();

    g_C64Bus.cia[0] = Cia_Create();
    g_C64Bus.cia[1] = Cia_Create();

    g_C64Bus.rom[0] = Memory_Create(13);
    g_C64Bus.rom[1] = Memory_Create(12);
    g_C64Bus.rom[2] = Memory_Create(13);

    Memory_LoadROM(g_C64Bus.rom[0], "../assets/basic.901226-01.bin");
    Memory_LoadROM(g_C64Bus.rom[1], "../assets/characters.901225-01.bin");
    Memory_LoadROM(g_C64Bus.rom[2], "../assets/kernal.901227-03.bin");

    g_C64Bus.ram = Memory_Create(16);
    g_C64Bus.color_ram = Memory_Create(10);

    // Memory_LoadContent(g_C64Bus.ram, 0);
    // Memory_LoadContent(g_C64Bus.color_ram, 0);
}

void C64Bus_Destroy()
{
    free(g_C64Bus.cia[0]);
    free(g_C64Bus.cia[1]);

    Memory_Destroy(g_C64Bus.rom[0]);
    Memory_Destroy(g_C64Bus.rom[1]);
    Memory_Destroy(g_C64Bus.rom[2]);
    Memory_Destroy(g_C64Bus.ram);
    Memory_Destroy(g_C64Bus.color_ram);
}

void C64Bus_Tick()
{
    Vic_Tick();
    Cia_Tick(g_C64Bus.cia[0]);

    if (C64Bus_CpuCanAccess())
    {
        CPU_Tick();
    }
}

uint8_t C64Bus_ReadPort(C64BusPortType portType)
{
    switch (portType)
    {
    case CPU_PORT:
        return g_cpu.port[1];
    case CIA_ONE_PRA:
        return g_C64Bus.cia[0]->port[0].pr;
    case CIA_ONE_PRB:
        return g_C64Bus.cia[0]->port[1].pr;
    case CIA_TWO_PRA:
        return g_C64Bus.cia[1]->port[0].pr;
    case CIA_TWO_PRB:
        return g_C64Bus.cia[1]->port[1].pr;
    }

    return 0;
}

void C64Bus_WritePort(C64BusPortType portType, uint8_t data)
{
    switch (portType)
    {
    case CPU_PORT:
        g_cpu.port[1] = data;
        break;
    case CIA_ONE_PRA:
        g_C64Bus.cia[0]->port[0].pr = data;
        break;
    case CIA_ONE_PRB:
        g_C64Bus.cia[0]->port[1].pr = data;
        break;
    case CIA_TWO_PRA:
        g_C64Bus.cia[1]->port[0].pr = data;
        break;
    case CIA_TWO_PRB:
        g_C64Bus.cia[1]->port[1].pr = data;
        break;
    }
}

void C64Bus_SetRDY(bool val)
{
    g_C64Bus.rdy = val;
}

void C64Bus_SetAEC(bool val)
{
    g_C64Bus.aec = val;
}

bool C64Bus_GetRDY()
{
    return g_C64Bus.rdy;
}

bool C64Bus_GetAEC()
{
    return g_C64Bus.aec;
}

void C64Bus_Release()
{
    C64Bus_SetRDY(1);
    C64Bus_SetAEC(1);
}

uint8_t C64Bus_GetVicMemoryBank()
{
    return ~(g_C64Bus.cia[1]->port[0].pr) & 0x03;
}

uint32_t *C64Bus_GetVicVideoFrame()
{
    return (uint32_t *)g_vic.videoFrame;
}

void C64Bus_CpuInterrupt(C64BusInterruptType interruptType)
{
    if (C64Bus_CpuCanAccess())
    {
        CPU_TriggerInterrupt(interruptType);
    }
}

Memory *C64Bus_GetRAM(void)
{
    return g_C64Bus.ram;
}

uint16_t C64Bus_VicRead(uint16_t addr)
{
    uint8_t vicMemoryBank = C64Bus_GetVicMemoryBank();
    uint16_t video_addr = (vicMemoryBank << 14) | (addr & 0x3FFF);

    uint8_t data = Memory_Read(g_C64Bus.ram, video_addr);
    uint8_t color = Memory_Read(g_C64Bus.color_ram, video_addr) & 0x0F;

    if ((vicMemoryBank == 0x00 && (addr >= 0x1000 && addr < 0x2000)) ||
        (vicMemoryBank == 0x02 && ((addr >= 0x9000 && addr < 0xA000))))
    {
        data = Memory_Read(g_C64Bus.rom[1], video_addr);
    }

    return (color << 8) | data;
}

bool C64Bus_CpuCanAccess()
{
    return C64Bus_GetAEC();
}

void C64Bus_SetCpuAccessRange()
{
    switch (g_cpu.port[1] & 0x07)
    {
    case 0x07:
        g_C64Bus.cpuAccessRange = 0x0D; // kernal + basic + io
        break;
    case 0x06:
        g_C64Bus.cpuAccessRange = 0x09; // kernal + io
        break;
    case 0x05:
        g_C64Bus.cpuAccessRange = 0x08; // io
        break;
    case 0x03:
        g_C64Bus.cpuAccessRange = 0x07; // kernal + character + basic
        break;
    case 0x02:
        g_C64Bus.cpuAccessRange = 0x02; // kernal + character
        break;
    case 0x01:
        g_C64Bus.cpuAccessRange = 0x01; // character
        break;
    default:
        g_C64Bus.cpuAccessRange = 0x00;
        break;
    }
}

uint8_t C64Bus_CpuRead(uint16_t addr)
{
    if (addr <= 0x01)
    {
        return g_cpu.port[addr];
    }

    if (C64Bus_InCpuAccessRange(KERNAL, addr, 0xE000, 0xFFFF))
    {
        return Memory_Read(g_C64Bus.rom[2], addr);
    }

    if (C64Bus_InCpuAccessRange(CHARACTER, addr, 0xD000, 0xDFFF))
    {
        return Memory_Read(g_C64Bus.rom[1], addr);
    }

    if (C64Bus_InCpuAccessRange(BASIC, addr, 0xA000, 0xBFFF))
    {
        return Memory_Read(g_C64Bus.rom[0], addr);
    }

    if (C64Bus_InCpuAccessRange(IO, addr, 0xD000, 0xD3FF))
    {
        return Vic_Read(addr);
    }

    if (C64Bus_InCpuAccessRange(IO, addr, 0xDC00, 0xDCFF))
    {
        return Cia_Read(g_C64Bus.cia[0], addr);
    }

    if (C64Bus_InCpuAccessRange(IO, addr, 0xDD00, 0xDDFF))
    {
        return Cia_Read(g_C64Bus.cia[1], addr);
    }

    if (C64Bus_InCpuAccessRange(IO, addr, 0xD800, 0xDBFF))
    {
        return Memory_Read(g_C64Bus.color_ram, addr);
    }

    return Memory_Read(g_C64Bus.ram, addr);
}

void C64Bus_CpuWrite(uint16_t addr, uint8_t data)
{
    if (addr <= 0x01)
    {
        g_cpu.port[addr] = data;
        C64Bus_SetCpuAccessRange();
    }

    if (C64Bus_InCpuAccessRange(IO, addr, 0xD000, 0xD3FF))
    {
        Vic_Write(addr, data);
    }
    else if (C64Bus_InCpuAccessRange(IO, addr, 0xDC00, 0xDCFF))
    {
        Cia_Write(g_C64Bus.cia[0], addr, data);
    }
    else if (C64Bus_InCpuAccessRange(IO, addr, 0xDD00, 0xDDFF))
    {
        Cia_Write(g_C64Bus.cia[1], addr, data);
    }
    else if (C64Bus_InCpuAccessRange(IO, addr, 0xD800, 0xDBFF))
    {
        Memory_Write(g_C64Bus.color_ram, addr, data);
    }
    else
    {
        Memory_Write(g_C64Bus.ram, addr, data);
    }
}

bool C64Bus_InCpuAccessRange(C64BusDeviceType type,
                             uint16_t addr,
                             uint16_t base,
                             uint16_t limit)
{
    return (g_C64Bus.cpuAccessRange & type) &&
           (addr >= base && addr <= limit);
}
