#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../c64bus.h"

CPU g_cpu;

void CPU_Init(void)
{
    g_cpu.cycle = 0;
    g_cpu.state = INTERRUPTED;

    CPU_CreateInsructionTable();
    CPU_TriggerInterrupt(INTERRUPT_RST);
}

void CPU_IRQ(void)
{
    CPU_PushWordStack(g_cpu.registers.pc);
    CPU_PushStack(g_cpu.registers.p & ~(1 << BREAK));

    CPU_SetFlag(INTERRUPT, true);

    uint8_t pcl = C64Bus_CpuRead(0xFFFE);
    uint8_t pch = C64Bus_CpuRead(0xFFFF);

    g_cpu.registers.pc = (pch << 8) | pcl;
}

void CPU_NMI(void)
{
    CPU_PushWordStack(g_cpu.registers.pc);
    CPU_PushStack(g_cpu.registers.p & ~(1 << BREAK));
    CPU_SetFlag(INTERRUPT, true);

    uint8_t pcl = C64Bus_CpuRead(0xFFFA);
    uint8_t pch = C64Bus_CpuRead(0xFFFB);

    g_cpu.registers.pc = (pch << 8) | pcl;
}

void CPU_RST(void)
{
    g_cpu.registers.p = 0x24;
    g_cpu.registers.s = 0xFD;
    g_cpu.registers.a = 0x00;
    g_cpu.registers.x = 0x00;
    g_cpu.registers.y = 0x00;

    g_cpu.port[0] = 0x7F;
    g_cpu.port[1] = 0x37;

    C64Bus_SetCpuAccessRange();

    uint8_t pcl = C64Bus_CpuRead(0xFFFC);
    uint8_t pch = C64Bus_CpuRead(0xFFFD);

    g_cpu.registers.pc = (pch << 8) | pcl;
}

void CPU_Tick(void)
{
    if (!C64Bus_GetRDY() && CPU_IsReadCycle())
    {
        C64Bus_SetAEC(0);
    }

    switch (g_cpu.state)
    {
    case EXECUTING:
        CPU_Execute();
        break;
    case INTERRUPTED:
        CPU_ExecuteInterrupt();
        break;
    }
}

void CPU_Execute(void)
{
    if (g_cpu.hasExtraCycles)
    {
        g_cpu.cycle--;
        g_cpu.hasExtraCycles = g_cpu.cycle != 0;
    }
    else if (!g_cpu.pendingInterrupt.isHandled)
    {
        g_cpu.state = INTERRUPTED;
    }
    else
    {
        g_cpu.opCode = C64Bus_CpuRead(g_cpu.registers.pc);
        CPU_Instruction instr = g_cpu.instructionTable[g_cpu.opCode];

        if (g_cpu.cycle == instr.cycles - 1)
        {
            g_cpu.registers.pc++;
            g_cpu.cycle = 0;

            uint16_t src = instr.addrModeExecute();
            instr.execute(src);

            g_cpu.hasExtraCycles = g_cpu.cycle != 0;
        }
        else
        {
            g_cpu.cycle++;
        }
    }
}

void CPU_ExecuteInterrupt(void)
{
    if (g_cpu.cycle == g_cpu.pendingInterrupt.cycles - 1)
    {
        g_cpu.pendingInterrupt.interruptFn();
        g_cpu.pendingInterrupt.isHandled = 1;

        g_cpu.cycle = 0;
        g_cpu.state = EXECUTING;
    }
    else
    {
        g_cpu.cycle++;
    }
}

bool CPU_IsReadCycle(void)
{
    CPU_MemoryAccess memoryAccess = g_cpu.state == EXECUTING ? g_cpu.instructionTable[g_cpu.opCode].memoryAccess : ACCESS_INTERRUPT;

    if ((memoryAccess & (1 << g_cpu.cycle)) || g_cpu.hasExtraCycles)
    {
        return 1;
    }

    return 0;
}

bool CPU_InstrTypeIsReadModifyWrite(void)
{
    return g_cpu.instructionTable[g_cpu.opCode].memoryAccess == ACCESS_ABSI_READ_MODIFY_WRITE;
}

void CPU_SetPendingInterrupt(uint8_t type, void (*interruptFn)(void))
{
    g_cpu.pendingInterrupt.type = type;
    g_cpu.pendingInterrupt.interruptFn = interruptFn;
    g_cpu.pendingInterrupt.cycles = type == INTERRUPT_RST ? 6 : 7;
    g_cpu.pendingInterrupt.isHandled = 0;
}

void CPU_TriggerInterrupt(uint8_t type)
{
    switch (type)
    {
    case INTERRUPT_IRQ:
        if (g_cpu.pendingInterrupt.isHandled && !CPU_TestFlag(INTERRUPT))
        {
            CPU_SetPendingInterrupt(INTERRUPT_IRQ, &CPU_IRQ);
        }
        break;
    case INTERRUPT_NMI:
        CPU_SetPendingInterrupt(INTERRUPT_NMI, &CPU_NMI);
        break;
    case INTERRUPT_RST:
        CPU_SetPendingInterrupt(INTERRUPT_RST, &CPU_RST);
        break;
    }
}

bool CPU_TestFlag(CPU_Flag flag)
{
    return g_cpu.registers.p & (1 << flag);
}

void CPU_SetFlag(CPU_Flag flag, bool val)
{
    if (val)
    {
        g_cpu.registers.p |= (1 << flag);
    }
    else
    {
        CPU_ClearFlag(flag);
    }
}

void CPU_ClearFlag(CPU_Flag flag)
{
    g_cpu.registers.p &= ~(1 << flag);
}

uint8_t CPU_GetCarry(void)
{
    return CPU_TestFlag(CARRY) ? 1 : 0;
}

uint8_t CPU_GetBorrow(void)
{
    return CPU_TestFlag(CARRY) ? 0 : 1;
}

void CPU_PushStack(uint8_t data)
{
    C64Bus_CpuWrite(0x100 + (g_cpu.registers.s)--, data);
}

void CPU_PushWordStack(uint16_t data)
{
    CPU_PushStack(data >> 8);
    CPU_PushStack(data & 0xFF);
}

uint8_t CPU_PopStack(void)
{
    return C64Bus_CpuRead(0x100 + (++(g_cpu.registers.s)));
}

uint16_t CPU_PopWordStack(void)
{
    uint8_t byteLow = CPU_PopStack();
    uint8_t byteHigh = CPU_PopStack();

    return (byteHigh << 8) | byteLow;
}

void CPU_BranchSet(CPU_Flag flag, uint16_t offset)
{
    if (CPU_TestFlag(flag))
    {
        g_cpu.cycle++;

        if ((g_cpu.registers.pc & 0xFF) + ((int16_t)offset) > 255)
        {
            g_cpu.cycle++;
        }

        g_cpu.registers.pc += (int16_t)offset;
    }
}

void CPU_BranchClear(CPU_Flag flag, uint16_t offset)
{
    if (!CPU_TestFlag(flag))
    {
        g_cpu.cycle++;

        if ((g_cpu.registers.pc & 0xFF) + ((int16_t)offset) > 255)
        {
            g_cpu.cycle++;
        }

        g_cpu.registers.pc += (int16_t)offset;
    }
}

void CPU_Compare(uint8_t reg, uint16_t src)
{
    uint16_t res = reg - C64Bus_CpuRead(src);

    CPU_SetFlag(CARRY, res < 0x100);
    CPU_SetFlag(ZERO, !(res & 0xFF));
    CPU_SetFlag(NEGATIVE, res & 0x80);
}

void CPU_Load(uint8_t *dst, uint16_t src)
{
    (*dst) = C64Bus_CpuRead(src);

    CPU_SetFlag(ZERO, !(*dst));
    CPU_SetFlag(NEGATIVE, (*dst & 0x80));
}

void CPU_Move(uint8_t *dst, uint16_t src)
{
    (*dst) = src;
    CPU_SetFlag(ZERO, !(*dst));
    CPU_SetFlag(NEGATIVE, *dst & 0x80);
}

void CPU_ArithmaticShiftLeft(uint8_t *src)
{
    CPU_SetFlag(CARRY, *src & 0x80);
    (*src) <<= 1;
    CPU_SetFlag(ZERO, !(*src));
    CPU_SetFlag(NEGATIVE, *src & 0x80);
}

void CPU_LogicalShiftRight(uint8_t *src)
{
    CPU_SetFlag(CARRY, *src & 0x01);
    (*src) >>= 1;
    CPU_SetFlag(ZERO, !(*src));
    CPU_ClearFlag(NEGATIVE);
}

void CPU_Increment(uint8_t *src)
{
    (*src)++;
    CPU_SetFlag(ZERO, !(*src));
    CPU_SetFlag(NEGATIVE, *src & 0x80);
}

void CPU_Decrement(uint8_t *src)
{
    (*src)--;
    CPU_SetFlag(ZERO, !(*src));
    CPU_SetFlag(NEGATIVE, *src & 0x80);
}

void CPU_RotateRight(uint8_t *src)
{
    uint8_t lsb = *src & 0x01;
    (*src) >>= 1;
    (*src) |= CPU_GetCarry() << 7;
    CPU_SetFlag(CARRY, lsb);
    CPU_SetFlag(ZERO, !(*src));
    CPU_SetFlag(NEGATIVE, *src & 0x80);
}

void CPU_RotateLeft(uint8_t *src)
{
    uint8_t msb = (*src & 0x80) >> 7;
    (*src) <<= 1;
    (*src) |= CPU_GetCarry();
    CPU_SetFlag(CARRY, msb);
    CPU_SetFlag(ZERO, !(*src));
    CPU_SetFlag(NEGATIVE, *src & 0x80);
}