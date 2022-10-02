#ifndef CPU_DEFINES_H
#define CPU_DEFINES_H

#include <stdint.h>
#include <stdbool.h>

// 1 = READ, 0 = WRITE

typedef enum
{
    ACCESS_INTERRUPT = 0b1100011,
    ACCESS_RETURN = 0b111111,
    ACCESS_PUSH = 0b011,
    ACCESS_PULL = 0b1111,
    ACCESS_JSR = 0b100111,
    ACCESS_ACC_IMPL_IMM = 0b11,
    ACCESS_ABS_JMP = 0b111,
    ACCESS_ABS_READ = 0b1111,
    ACCESS_ABS_READ_MODIFY_WRITE = 0b001111,
    ACCESS_ABS_WRITE = 0b0111,
    ACCESS_ZPG_READ = 0b111,
    ACCESS_ZPG_READ_MODIFY_WRITE = 0b00111,
    ACCESS_ZPG_WRITE = 0b011,
    ACCESS_ZPGI_READ = 0b1111,
    ACCESS_ZPGI_READ_MODIFY_WRITE = 0b001111,
    ACCESS_ZPGI_WRITE = 0b0111,
    ACCESS_ABSI_READ = 0b11111,
    ACCESS_ABSI_READ_MODIFY_WRITE = 0b0011111,
    ACCESS_ABSI_WRITE = 0b01111,
    ACCESS_REL = 0b1111,
    ACCESS_XIND_READ = 0b111111,
    ACCESS_XIND_WRITE = 0b011111,
    ACCESS_INDY_READ = 0b111111,
    ACCESS_INDY_WRITE = 0b011111,
    ACCESS_IND_JMP = 0b11111,

} CPU_MemoryAccess;

typedef struct
{
    uint16_t pc;
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t s;
    uint8_t p;

} CPU_Registers;

typedef struct
{
    void (*execute)(uint16_t);
    uint16_t (*addrModeExecute)(void);
    CPU_MemoryAccess memoryAccess;
    uint8_t cycles;

} CPU_Instruction;

typedef struct
{
    void (*interruptFn)(void);
    uint8_t type;
    uint8_t cycles;
    bool isHandled;

} CPU_Interrupt;

typedef enum
{
    EXECUTING = 0,
    INTERRUPTED,

} CPU_State;

typedef enum
{
    CARRY = 0,
    ZERO,
    INTERRUPT,
    DECIMAL,
    BREAK,
    UNUSED,
    OVERFLOW,
    NEGATIVE,

} CPU_Flag;

#endif