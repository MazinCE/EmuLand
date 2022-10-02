#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include "display.h"
#include "keypad.h"

#define INSTR_VX(w) (((w)&0x0F00) >> 8)
#define INSTR_VY(w) (((w)&0x00F0) >> 4)
#define INSTR_NNN(w) ((w)&0x0FFF)
#define INSTR_NN(w) ((w)&0x00FF)
#define INSTR_N(w) ((w)&0x000F)
#define BIT_TEST(b, n) (b & (1 << (n)))
#define INSTR_OPCODE(w) ((w & 0xF000) >> 12)

#define PROGRAM_MEMORY_SIZE 4096
#define STACK_SIZE 16
#define FONT_START_ADDRESS 80
#define PROGRAM_START_ADDRESS 512

typedef struct
{
    uint16_t pc;
    uint16_t i;
    uint8_t dt;
    uint8_t st;
    uint8_t sp;
    uint16_t ir;
    uint8_t v[16];
} CPU;

typedef struct
{
    uint8_t program[PROGRAM_MEMORY_SIZE];
    uint16_t stack[STACK_SIZE];
} Memory;

typedef struct
{
    CPU cpu;
    Memory mem;
} Chip8;

typedef void (*OpcodeFn)(void);

void Chip8_Init(void);
void Chip8_Destory(void);

int Chip8_LoadRom(const char *path);
void Chip8_HandleInput(SDL_Event e);

void Chip8_LogStatus(void);
void Chip8_UpdateTimers(void);
void Chip8_Fetch(void);
void Chip8_Execute(void);
void Chip8_Tick(uint8_t cycleDelay);

void Chip8_ClearDisplay(void);
void Chip8_Draw(void);

void Chip8_OP0(void);
void Chip8_OP1(void);
void Chip8_OP2(void);
void Chip8_OP3(void);
void Chip8_OP4(void);
void Chip8_OP5(void);
void Chip8_OP6(void);
void Chip8_OP7(void);
void Chip8_OP8(void);
void Chip8_OP9(void);
void Chip8_OPA(void);
void Chip8_OPB(void);
void Chip8_OPC(void);
void Chip8_OPD(void);
void Chip8_OPE(void);
void Chip8_OPF(void);

static const OpcodeFn OPCODE_TABLE[16] =
    {
        Chip8_OP0,
        Chip8_OP1,
        Chip8_OP2,
        Chip8_OP3,
        Chip8_OP4,
        Chip8_OP5,
        Chip8_OP6,
        Chip8_OP7,
        Chip8_OP8,
        Chip8_OP9,
        Chip8_OPA,
        Chip8_OPB,
        Chip8_OPC,
        Chip8_OPD,
        Chip8_OPE,
        Chip8_OPF,
};

static const uint8_t FONT_SET[80] =
    {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

#endif
