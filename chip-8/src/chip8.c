#include "../include/chip8.h"
#include <unistd.h>
#include <time.h>

static Chip8 g_Chip8;

void Chip8_Init(void)
{
    srand(time(0));

    CPU *cpu = &(g_Chip8.cpu);
    cpu->pc = PROGRAM_START_ADDRESS;
    cpu->sp = 0;
    cpu->dt = 0;
    cpu->st = 0;
    cpu->i = 0;
    memset(cpu->v, 0, 16);
    memcpy(g_Chip8.mem.program + FONT_START_ADDRESS, FONT_SET, 80);

    Display_Init();
    Keypad_Init();
}

void Chip8_Destory(void)
{
    Display_Destroy();
}

int Chip8_LoadRom(const char *path)
{
    if (access(path, F_OK) == -1)
    {
        printf("Unable to load rom...\n");
        return -1;
    }

    FILE *rom = fopen(path, "rb");
    fseek(rom, 0, SEEK_END);
    size_t romSize = ftell(rom);
    rewind(rom);
    fread(g_Chip8.mem.program + PROGRAM_START_ADDRESS, romSize, 1, rom);
    fclose(rom);

    return 0;
}

void Chip8_HandleInput(SDL_Event e)
{
    Keypad_RegisterKeyState(e);
}

void Chip8_LogStatus(void)
{
    CPU *cpu = &(g_Chip8.cpu);
    ;

    printf("Chip8 Status:\n\n");
    printf("PC = $%04X\n", cpu->pc);
    printf("IR = $%04X\n", cpu->ir);
    printf("SP = $%04X\n", cpu->sp);
    printf("I  = $%04X\n", cpu->i);
    printf("DT = $%04X\n", cpu->dt);
    printf("ST = $%04X\n\n", cpu->st);

    for (uint8_t i = 0; i < 4; ++i)
    {
        for (uint8_t j = 0; j < 4; ++j)
        {
            printf("V%01X = $%04X  ", j + i * 0x04, cpu->v[j + i * 4]);
        }
        printf("\n");
    }
}

void Chip8_UpdateTimers(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    if (cpu->dt > 0)
    {
        --cpu->dt;
    }

    if (cpu->st > 0)
    {
        --cpu->st;
    }
}

void Chip8_Fetch()
{
    CPU *cpu = &(g_Chip8.cpu);
    Memory *mem = &(g_Chip8.mem);

    cpu->ir = (uint8_t)mem->program[cpu->pc];
    cpu->ir <<= 8;
    cpu->ir |= (uint8_t)mem->program[cpu->pc + 1];
    cpu->pc += 2;
}

void Chip8_Execute()
{
    OPCODE_TABLE[INSTR_OPCODE(g_Chip8.cpu.ir)]();
}

void Chip8_Tick(uint8_t cycleDelay)
{
    for (uint8_t i = 0; i < cycleDelay; ++i)
    {
        Chip8_Fetch();
        Chip8_Execute();
    }

    Chip8_UpdateTimers();
}

void Chip8_Draw()
{
    Display_Clear();
    Display_Render();
}

void Chip8_OP0(void)
{
    CPU *cpu = &(g_Chip8.cpu);
    uint8_t nn = INSTR_NN(cpu->ir);

    if (nn == 0xE0)
    {
        // CLS
        Display_ClearFrameBuffer();
    }
    else if (nn == 0xEE)
    {
        // RET
        cpu->pc = g_Chip8.mem.stack[--cpu->sp];
    }
}

void Chip8_OP1(void)
{
    CPU *cpu = &(g_Chip8.cpu);
    // JP ADDR
    cpu->pc = INSTR_NNN(cpu->ir);
}

void Chip8_OP2(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    // CALL ADDR
    g_Chip8.mem.stack[cpu->sp++] = cpu->pc;
    cpu->pc = INSTR_NNN(cpu->ir);
}

void Chip8_OP3(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    // SE VX,KK
    if (cpu->v[INSTR_VX(cpu->ir)] == INSTR_NN(cpu->ir))
    {
        cpu->pc += 2;
    }
}

void Chip8_OP4(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    // SNE VX,KK
    if (cpu->v[INSTR_VX(cpu->ir)] != INSTR_NN(cpu->ir))
    {
        cpu->pc += 2;
    }
}

void Chip8_OP5(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    // SE VX,VY
    if (cpu->v[INSTR_VX(cpu->ir)] == cpu->v[INSTR_VY(cpu->ir)])
    {
        cpu->pc += 2;
    }
}

void Chip8_OP6(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    // LD VX,KK
    cpu->v[INSTR_VX(cpu->ir)] = INSTR_NN(cpu->ir);
}

void Chip8_OP7(void)
{
    CPU *cpu = &(g_Chip8.cpu);
    // ADD VX,KK
    cpu->v[INSTR_VX(cpu->ir)] += INSTR_NN(cpu->ir);
}

void Chip8_OP8(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    uint8_t x = INSTR_VX(cpu->ir);
    uint8_t y = INSTR_VY(cpu->ir);

    switch (INSTR_N(cpu->ir))
    {
    case 0x00:
        // LD VX,VY
        cpu->v[x] = cpu->v[y];
        break;
    case 0x01:
        // OR VX,VY
        cpu->v[x] |= cpu->v[y];
        break;
    case 0x02:
        // AND VX,VY
        cpu->v[x] &= cpu->v[y];
        break;
    case 0x03:
        // XOR VX,VY
        cpu->v[x] ^= cpu->v[y];
        break;
    case 0x04:
        // ADD VX,VY
        cpu->v[15] = (cpu->v[x] + cpu->v[y]) > 255;
        cpu->v[x] = (cpu->v[x] + cpu->v[y]) & 255;
        break;
    case 0x05:
        // SUB VX,VY
        cpu->v[15] = cpu->v[x] > cpu->v[y];
        cpu->v[x] -= cpu->v[y];
        break;
    case 0x06:
        // SHR VX,1
        cpu->v[15] = BIT_TEST(cpu->v[x], 0);
        cpu->v[x] >>= 1;
        break;
    case 0x07:
        // SUBN VX,VY
        cpu->v[15] = cpu->v[y] > cpu->v[x];
        cpu->v[x] = cpu->v[y] - cpu->v[x];
        break;
    case 0x0E:
        // SHL VX,1
        cpu->v[15] = BIT_TEST(cpu->v[x], 7) ? 1 : 0;
        cpu->v[x] <<= 1;
        break;
    default:
        break;
    }
}

void Chip8_OP9(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    // SNE VX != VY
    if (cpu->v[INSTR_VX(cpu->ir)] != cpu->v[INSTR_VY(cpu->ir)])
    {
        cpu->pc += 2;
    }
}

void Chip8_OPA(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    // LD I,ADDR
    cpu->i = INSTR_NNN(cpu->ir);
}

void Chip8_OPB(void)
{
    CPU *cpu = &(g_Chip8.cpu);
    // JP V0,ADDR
    cpu->pc = INSTR_NNN(cpu->ir) + cpu->v[0];
}

void Chip8_OPC(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    /// RND VX,KK
    cpu->v[INSTR_VX(cpu->ir)] = (rand() % 256) & INSTR_NN(cpu->ir);
}

void Chip8_OPD(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    Memory *mem = &(g_Chip8.mem);

    // DRW VX,VY,N
    uint8_t vx = cpu->v[INSTR_VX(cpu->ir)];
    uint8_t vy = cpu->v[INSTR_VY(cpu->ir)];
    uint8_t n = INSTR_N(cpu->ir);

    uint8_t x = vx % CHIP8_SCREEN_WIDTH;
    uint8_t y = vy % CHIP8_SCREEN_HEIGHT;

    cpu->v[15] = 0;
    uint32_t srcPixel;
    uint8_t sprPixel;

    for (uint8_t i = 0; i < n; ++i)
    {
        for (uint8_t j = 0; j < 8; ++j)
        {
            sprPixel = BIT_TEST(mem->program[cpu->i + i], 7 - j) ? 1 : 0;
            srcPixel = Display_GetPixel(x + j, y + i);

            if (sprPixel)
            {
                if (srcPixel)
                {
                    cpu->v[15] = 1;
                }

                Display_SetPixel(x + j, y + i, srcPixel ^ 0xFFFFFFFF);
            }
        }
    }

    Display_SetDirty();
}

void Chip8_OPE(void)
{
    CPU *cpu = &(g_Chip8.cpu);

    uint8_t nn = INSTR_NN(cpu->ir);
    uint8_t vx = cpu->v[INSTR_VX(cpu->ir)];

    Key k = Keypad_GetKey(vx);

    // SKP VX
    if ((nn == 0x9E && k.isPressed) ||
        // SKNP VX
        (nn == 0xA1 && !k.isPressed))
    {
        cpu->pc += 2;
    }
}

void Chip8_OPF(void)
{
    CPU *cpu = &(g_Chip8.cpu);
    Memory *mem = &(g_Chip8.mem);

    uint8_t x = INSTR_VX(cpu->ir);

    switch (INSTR_NN(cpu->ir))
    {
    case 0x07:
        // LD VX,DT
        cpu->v[x] = cpu->dt;
        break;
    case 0x0A:
        // LD VX,K
        for (uint8_t i = 0; i < 16; ++i)
        {
            Key k = Keypad_GetKey(i);
            if (k.isPressed)
            {
                cpu->v[x] = k.index;
                return;
            }
        }
        cpu->pc -= 2;
        break;
    case 0x15:
        // LD DT,VX
        cpu->dt = cpu->v[x];
        break;
    case 0x18:
        // LD ST,VX
        cpu->st = cpu->v[x];
        break;
    case 0x1E:
        // ADD I,VX
        cpu->i += cpu->v[x];
        break;
    case 0x29:
        // LD F,VX
        cpu->i = FONT_START_ADDRESS + cpu->v[x] * 5;
        break;
    case 0x33:
        // LD B,VX
        mem->program[cpu->i] = cpu->v[x] / 100;
        mem->program[cpu->i + 1] = (cpu->v[x] / 10) % 10;
        mem->program[cpu->i + 2] = (cpu->v[x] % 100) % 10;
        break;
    case 0x55:
        // LD [I],VX
        for (uint8_t i = 0; i <= x; ++i)
        {
            mem->program[cpu->i + i] = cpu->v[i];
        }
        break;
    case 0x65:
        // LD VX,[I]
        for (uint8_t i = 0; i <= x; ++i)
        {
            cpu->v[i] = mem->program[cpu->i + i];
        }
        break;
    }
}
