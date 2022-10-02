#include "addr_modes.h"
#include "cpu.h"
#include "../c64bus.h"

uint16_t CPU_AddrMode_ACC()
{
    return 0;
}

uint16_t CPU_AddrMode_ABS()
{
    uint8_t addrLow = C64Bus_CpuRead(g_cpu.registers.pc++);
    uint8_t addrHigh = C64Bus_CpuRead(g_cpu.registers.pc++);

    return (addrHigh << 8) | addrLow;
}

uint16_t CPU_AddrMode_ABSX()
{
    uint16_t absAddr = CPU_AddrMode_ABS();

    if (!CPU_InstrTypeIsReadModifyWrite() && (absAddr & 0xFF) + g_cpu.registers.x > 255)
    {
        g_cpu.cycle++;
    }

    return absAddr + g_cpu.registers.x;
}

uint16_t CPU_AddrMode_ABSY()
{
    uint16_t absAddr = CPU_AddrMode_ABS();

    if (!CPU_InstrTypeIsReadModifyWrite() && (absAddr & 0xFF) + g_cpu.registers.y > 255)
    {
        g_cpu.cycle++;
    }

    return absAddr + g_cpu.registers.y;
}

uint16_t CPU_AddrMode_IMM()
{
    return g_cpu.registers.pc++;
}

uint16_t CPU_AddrMode_IMPL()
{
    return 0;
}

uint16_t CPU_AddrMode_IND()
{
    uint8_t pointerLow = C64Bus_CpuRead(g_cpu.registers.pc++);
    uint8_t pointerHigh = C64Bus_CpuRead(g_cpu.registers.pc++);

    uint16_t pointer = (pointerHigh << 8) | pointerLow;

    uint8_t addrLow = C64Bus_CpuRead(pointer);

    uint16_t effAddrHigh = pointerLow == 0xFF ? pointer & 0xF00 : pointer + 1;
    uint8_t addrHigh = C64Bus_CpuRead(effAddrHigh);

    return (addrHigh << 8) | addrLow;
}

uint16_t CPU_AddrMode_XIND()
{
    uint8_t pointer = C64Bus_CpuRead(g_cpu.registers.pc++) + g_cpu.registers.x;

    uint8_t addrLow = C64Bus_CpuRead(pointer);
    uint8_t addrHigh = C64Bus_CpuRead(pointer == 0xFF ? 0x00 : pointer + 1);

    return (addrHigh << 8) | addrLow;
}

uint16_t CPU_AddrMode_INDY()
{
    uint8_t pointer = C64Bus_CpuRead(g_cpu.registers.pc++);

    uint8_t addrLow = C64Bus_CpuRead(pointer);
    uint8_t addrHigh = C64Bus_CpuRead(pointer == 0xFF ? 0x00 : pointer + 1);

    uint16_t addr = (addrHigh << 8) | addrLow;

    if ((addr & 0xFF) + g_cpu.registers.y > 255)
    {
        g_cpu.cycle++;
    }

    return addr + g_cpu.registers.y;
}

uint16_t CPU_AddrMode_REL()
{
    uint8_t offset = C64Bus_CpuRead(g_cpu.registers.pc++);

    return offset & 0x80 ? (0xFF00 | offset) : offset;
}

uint16_t CPU_AddrMode_ZPG()
{
    return C64Bus_CpuRead(g_cpu.registers.pc++);
}

uint16_t CPU_AddrMode_ZPGX()
{
    return (CPU_AddrMode_ZPG() + g_cpu.registers.x) & 0xFF;
}

uint16_t CPU_AddrMode_ZPGY()
{
    return (CPU_AddrMode_ZPG() + g_cpu.registers.y) & 0xFF;
}
