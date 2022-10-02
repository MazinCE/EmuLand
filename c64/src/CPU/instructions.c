#include "instructions.h"
#include "cpu.h"
#include "../c64bus.h"

void CPU_Instruction_ADC(uint16_t src)
{
    uint8_t m = C64Bus_CpuRead(src);

    uint16_t res = g_cpu.registers.a + m + CPU_GetCarry();

    CPU_SetFlag(ZERO, !(res & 0xFF));

    if (CPU_TestFlag(DECIMAL))
    {
        if (((g_cpu.registers.a & 0xF) + (m & 0xF) + CPU_GetCarry()) > 9)
        {
            res += 6;
        }

        CPU_SetFlag(NEGATIVE, res & 0x80);
        CPU_SetFlag(OVERFLOW, !((g_cpu.registers.a ^ m) & 0x80) && ((g_cpu.registers.a ^ res) & 0x80));

        if (res > 0x99)
        {
            res += 96;
        }

        CPU_SetFlag(CARRY, res > 0x99);
    }
    else
    {
        CPU_SetFlag(OVERFLOW, !((g_cpu.registers.a ^ m) & 0x80) && ((g_cpu.registers.a ^ res) & 0x80));
        CPU_SetFlag(NEGATIVE, res & 0x80);
        CPU_SetFlag(CARRY, res > 0xff);
    }

    g_cpu.registers.a = res & 0xFF;
}

void CPU_Instruction_AND(uint16_t src)
{
    g_cpu.registers.a &= C64Bus_CpuRead(src);
    CPU_SetFlag(ZERO, !g_cpu.registers.a);
    CPU_SetFlag(NEGATIVE, g_cpu.registers.a & 0x80);
}

void CPU_Instruction_ASL(uint16_t src)
{
    uint8_t m = C64Bus_CpuRead(src);
    CPU_ArithmaticShiftLeft(&m);
    C64Bus_CpuWrite(src, m);
}

void CPU_Instruction_BCC(uint16_t src)
{
    CPU_BranchClear(CARRY, src);
}

void CPU_Instruction_BCS(uint16_t src)
{
    CPU_BranchSet(CARRY, src);
}

void CPU_Instruction_BEQ(uint16_t src)
{
    CPU_BranchSet(ZERO, src);
}

void CPU_Instruction_BIT(uint16_t src)
{
    uint8_t m = C64Bus_CpuRead(src);

    CPU_SetFlag(NEGATIVE, m & 0x80);
    CPU_SetFlag(OVERFLOW, m & 0x40);
    CPU_SetFlag(ZERO, !(g_cpu.registers.a & m));
}

void CPU_Instruction_BMI(uint16_t src)
{
    CPU_BranchSet(NEGATIVE, src);
}

void CPU_Instruction_BNE(uint16_t src)
{
    CPU_BranchClear(ZERO, src);
}

void CPU_Instruction_BPL(uint16_t src)
{
    CPU_BranchClear(NEGATIVE, src);
}

void CPU_Instruction_BRK(uint16_t src)
{
    CPU_PushWordStack(g_cpu.registers.pc);

    CPU_SetFlag(INTERRUPT, true);
    CPU_PushStack(g_cpu.registers.p | (1 << BREAK));

    uint8_t pcl = C64Bus_CpuRead(0xFFFE);
    uint8_t pch = C64Bus_CpuRead(0xFFFF);

    g_cpu.registers.pc = (pch << 8) | pcl;
}

void CPU_Instruction_BVC(uint16_t src)
{
    CPU_BranchClear(OVERFLOW, src);
}

void CPU_Instruction_BVS(uint16_t src)
{
    CPU_BranchSet(OVERFLOW, src);
}

void CPU_Instruction_CLC(uint16_t src)
{
    CPU_ClearFlag(CARRY);
}

void CPU_Instruction_CLD(uint16_t src)
{
    CPU_ClearFlag(DECIMAL);
}

void CPU_Instruction_CLI(uint16_t src)
{
    CPU_ClearFlag(INTERRUPT);
}

void CPU_Instruction_CLV(uint16_t src)
{
    CPU_ClearFlag(OVERFLOW);
}

void CPU_Instruction_CMP(uint16_t src)
{
    CPU_Compare(g_cpu.registers.a, src);
}

void CPU_Instruction_CPX(uint16_t src)
{
    CPU_Compare(g_cpu.registers.x, src);
}

void CPU_Instruction_CPY(uint16_t src)
{
    CPU_Compare(g_cpu.registers.y, src);
}

void CPU_Instruction_DEC(uint16_t src)
{
    uint8_t m = C64Bus_CpuRead(src);
    CPU_Decrement(&m);
    C64Bus_CpuWrite(src, m);
}

void CPU_Instruction_DEX(uint16_t src)
{
    CPU_Decrement(&g_cpu.registers.x);
}

void CPU_Instruction_DEY(uint16_t src)
{
    CPU_Decrement(&g_cpu.registers.y);
}

void CPU_Instruction_EOR(uint16_t src)
{
    g_cpu.registers.a ^= C64Bus_CpuRead(src);
    CPU_SetFlag(ZERO, !g_cpu.registers.a);
    CPU_SetFlag(NEGATIVE, g_cpu.registers.a & 0x80);
}

void CPU_Instruction_INC(uint16_t src)
{
    uint8_t m = C64Bus_CpuRead(src);
    CPU_Increment(&m);
    C64Bus_CpuWrite(src, m);
}

void CPU_Instruction_INX(uint16_t src)
{
    CPU_Increment(&g_cpu.registers.x);
}

void CPU_Instruction_INY(uint16_t src)
{
    CPU_Increment(&g_cpu.registers.y);
}

void CPU_Instruction_JMP(uint16_t src)
{
    g_cpu.registers.pc = src;
}

void CPU_Instruction_JSR(uint16_t src)
{
    CPU_PushWordStack(--(g_cpu.registers.pc));
    g_cpu.registers.pc = src;
}

void CPU_Instruction_LDA(uint16_t src)
{
    CPU_Load(&(g_cpu.registers.a), src);
}

void CPU_Instruction_LDX(uint16_t src)
{
    CPU_Load(&(g_cpu.registers.x), src);
}

void CPU_Instruction_LDY(uint16_t src)
{
    CPU_Load(&(g_cpu.registers.y), src);
}

void CPU_Instruction_LSR(uint16_t src)
{
    uint8_t m = C64Bus_CpuRead(src);
    CPU_LogicalShiftRight(&m);
    C64Bus_CpuWrite(src, m);
}

void CPU_Instruction_NOP(uint16_t src)
{
}

void CPU_Instruction_ORA(uint16_t src)
{
    g_cpu.registers.a |= C64Bus_CpuRead(src);
    CPU_SetFlag(ZERO, !(g_cpu.registers.a));
    CPU_SetFlag(NEGATIVE, g_cpu.registers.a & 0x80);
}

void CPU_Instruction_PHA(uint16_t src)
{
    CPU_PushStack(g_cpu.registers.a);
}

void CPU_Instruction_PHP(uint16_t src)
{
    CPU_PushStack(g_cpu.registers.p | (1 << BREAK));
}

void CPU_Instruction_PLA(uint16_t src)
{
    g_cpu.registers.a = CPU_PopStack();
    CPU_SetFlag(ZERO, !g_cpu.registers.a);
    CPU_SetFlag(NEGATIVE, g_cpu.registers.a & 0x80);
}

void CPU_Instruction_PLP(uint16_t src)
{
    g_cpu.registers.p = CPU_PopStack() | (1 << UNUSED);
}

void CPU_Instruction_ROL(uint16_t src)
{
    uint8_t m = C64Bus_CpuRead(src);
    CPU_RotateLeft(&m);
    C64Bus_CpuWrite(src, m);
}

void CPU_Instruction_ROR(uint16_t src)
{
    uint8_t m = C64Bus_CpuRead(src);
    CPU_RotateRight(&m);
    C64Bus_CpuWrite(src, m);
}

void CPU_Instruction_RTI(uint16_t src)
{
    g_cpu.registers.p = CPU_PopStack() | (1 << UNUSED);
    g_cpu.registers.pc = CPU_PopWordStack();
}

void CPU_Instruction_RTS(uint16_t src)
{
    g_cpu.registers.pc = CPU_PopWordStack() + 1;
}

void CPU_Instruction_SBC(uint16_t src)
{
    uint8_t m = C64Bus_CpuRead(src);

    uint16_t res = g_cpu.registers.a - m - CPU_GetBorrow();

    CPU_SetFlag(ZERO, !(res & 0xff));
    CPU_SetFlag(OVERFLOW, ((g_cpu.registers.a ^ m) & 0x80) && ((g_cpu.registers.a ^ res) & 0x80));
    CPU_SetFlag(NEGATIVE, res & 0x80);

    if (CPU_TestFlag(DECIMAL))
    {
        if (((g_cpu.registers.a & 0x0F) - CPU_GetBorrow()) < (m & 0x0F))
        {
            res -= 6;
        }

        if (res > 0x99)
        {
            res -= 0x60;
        }
    }

    CPU_SetFlag(CARRY, res < 0x100);
    g_cpu.registers.a = res & 0xFF;
}

void CPU_Instruction_SEC(uint16_t src)
{
    CPU_SetFlag(CARRY, true);
}

void CPU_Instruction_SED(uint16_t src)
{
    CPU_SetFlag(DECIMAL, true);
}

void CPU_Instruction_SEI(uint16_t src)
{
    CPU_SetFlag(INTERRUPT, true);
}

void CPU_Instruction_STA(uint16_t src)
{
    C64Bus_CpuWrite(src, g_cpu.registers.a);
}

void CPU_Instruction_STX(uint16_t src)
{
    C64Bus_CpuWrite(src, g_cpu.registers.x);
}

void CPU_Instruction_STY(uint16_t src)
{
    C64Bus_CpuWrite(src, g_cpu.registers.y);
}

void CPU_Instruction_TAX(uint16_t src)
{
    CPU_Move(&(g_cpu.registers.x), g_cpu.registers.a);
}

void CPU_Instruction_TAY(uint16_t src)
{
    CPU_Move(&(g_cpu.registers.y), g_cpu.registers.a);
}

void CPU_Instruction_TSX(uint16_t src)
{
    CPU_Move(&(g_cpu.registers.x), g_cpu.registers.s);
}

void CPU_Instruction_TXA(uint16_t src)
{
    CPU_Move(&(g_cpu.registers.a), g_cpu.registers.x);
}

void CPU_Instruction_TXS(uint16_t src)
{
    g_cpu.registers.s = g_cpu.registers.x;
}

void CPU_Instruction_TYA(uint16_t src)
{
    CPU_Move(&(g_cpu.registers.a), g_cpu.registers.y);
}

void CPU_Instruction_ASL_ACC(uint16_t src)
{
    CPU_ArithmaticShiftLeft(&(g_cpu.registers.a));
}

void CPU_Instruction_LSR_ACC(uint16_t src)
{
    CPU_LogicalShiftRight(&(g_cpu.registers.a));
}

void CPU_Instruction_ROL_ACC(uint16_t src)
{
    CPU_RotateLeft(&(g_cpu.registers.a));
}

void CPU_Instruction_ROR_ACC(uint16_t src)
{
    CPU_RotateRight(&(g_cpu.registers.a));
}