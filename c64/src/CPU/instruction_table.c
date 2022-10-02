#include "cpu.h"
#include "instructions.h"
#include "addr_modes.h"

void CPU_CreateInsructionTable()
{
    // ADC
    CPU_Instruction adcImm = {
        .execute = &CPU_Instruction_ADC,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x69] = adcImm;

    CPU_Instruction adcZpg = {
        .execute = &CPU_Instruction_ADC,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x65] = adcZpg;

    CPU_Instruction adcZpgx = {
        .execute = &CPU_Instruction_ADC,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x75] = adcZpgx;

    CPU_Instruction adcAbs = {
        .execute = &CPU_Instruction_ADC,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4};

    g_cpu.instructionTable[0x6D] = adcAbs;

    CPU_Instruction adcAbsx = {
        .execute = &CPU_Instruction_ADC,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x7D] = adcAbsx;

    CPU_Instruction adcAbsy = {
        .execute = &CPU_Instruction_ADC,
        .addrModeExecute = &CPU_AddrMode_ABSY,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x79] = adcAbsy;

    CPU_Instruction adcXind = {
        .execute = &CPU_Instruction_ADC,
        .addrModeExecute = &CPU_AddrMode_XIND,
        .memoryAccess = ACCESS_XIND_READ,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x61] = adcXind;

    CPU_Instruction adcIndy = {
        .execute = &CPU_Instruction_ADC,
        .addrModeExecute = &CPU_AddrMode_INDY,
        .memoryAccess = ACCESS_INDY_READ,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x71] = adcIndy;

    // AND
    CPU_Instruction andImm = {
        .execute = &CPU_Instruction_AND,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x29] = andImm;

    CPU_Instruction andZpg = {
        .execute = &CPU_Instruction_AND,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x25] = andZpg;

    CPU_Instruction andZpgx = {
        .execute = &CPU_Instruction_AND,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x35] = andZpgx;

    CPU_Instruction andAbs = {
        .execute = &CPU_Instruction_AND,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x2D] = andAbs;

    CPU_Instruction andAbsx = {
        .execute = &CPU_Instruction_AND,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x3D] = andAbsx;

    CPU_Instruction andAbsy = {
        .execute = &CPU_Instruction_AND,
        .addrModeExecute = &CPU_AddrMode_ABSY,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x39] = andAbsy;

    CPU_Instruction andXind = {
        .execute = &CPU_Instruction_AND,
        .addrModeExecute = &CPU_AddrMode_XIND,
        .memoryAccess = ACCESS_XIND_READ,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x21] = andXind;

    CPU_Instruction andIndy = {
        .execute = &CPU_Instruction_AND,
        .addrModeExecute = &CPU_AddrMode_INDY,
        .memoryAccess = ACCESS_INDY_READ,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x31] = andIndy;

    // ASL
    CPU_Instruction aslAcc = {
        .execute = &CPU_Instruction_ASL_ACC,
        .addrModeExecute = &CPU_AddrMode_ACC,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x0A] = aslAcc;

    CPU_Instruction aslZpg = {
        .execute = &CPU_Instruction_ASL,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ_MODIFY_WRITE,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x06] = aslZpg;

    CPU_Instruction aslZpgx = {
        .execute = &CPU_Instruction_ASL,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x16] = aslZpgx;

    CPU_Instruction aslAbs = {
        .execute = &CPU_Instruction_ASL,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x0E] = aslAbs;

    CPU_Instruction aslAbsx = {
        .execute = &CPU_Instruction_ASL,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ_MODIFY_WRITE,
        .cycles = 7,
    };

    g_cpu.instructionTable[0x1E] = aslAbsx;

    // BCC
    CPU_Instruction bcc = {
        .execute = &CPU_Instruction_BCC,
        .addrModeExecute = &CPU_AddrMode_REL,
        .memoryAccess = ACCESS_REL,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x90] = bcc;

    // BCS
    CPU_Instruction bcs = {
        .execute = &CPU_Instruction_BCS,
        .addrModeExecute = &CPU_AddrMode_REL,
        .memoryAccess = ACCESS_REL,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xB0] = bcs;

    // BEQ
    CPU_Instruction beq = {
        .execute = &CPU_Instruction_BEQ,
        .addrModeExecute = &CPU_AddrMode_REL,
        .memoryAccess = ACCESS_REL,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xF0] = beq;

    // BIT
    CPU_Instruction bitZpg = {
        .execute = &CPU_Instruction_BIT,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x24] = bitZpg;

    CPU_Instruction bitAbs = {
        .execute = &CPU_Instruction_BIT,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x2C] = bitAbs;

    // BMI
    CPU_Instruction bmi = {
        .execute = &CPU_Instruction_BMI,
        .addrModeExecute = &CPU_AddrMode_REL,
        .memoryAccess = ACCESS_REL,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x30] = bmi;

    // BNE
    CPU_Instruction bne = {
        .execute = &CPU_Instruction_BNE,
        .addrModeExecute = &CPU_AddrMode_REL,
        .memoryAccess = ACCESS_REL,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xD0] = bne;

    // BPL
    CPU_Instruction bpl = {
        .execute = &CPU_Instruction_BPL,
        .addrModeExecute = &CPU_AddrMode_REL,
        .memoryAccess = ACCESS_REL,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x10] = bpl;

    // BRK
    CPU_Instruction brk = {
        .execute = &CPU_Instruction_BRK,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_INTERRUPT,
        .cycles = 7,
    };

    g_cpu.instructionTable[0x00] = brk;

    // BVC
    CPU_Instruction bvc = {
        .execute = &CPU_Instruction_BVC,
        .addrModeExecute = &CPU_AddrMode_REL,
        .memoryAccess = ACCESS_REL,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x50] = bvc;

    // BVS
    CPU_Instruction bvs = {
        .execute = &CPU_Instruction_BVS,
        .addrModeExecute = &CPU_AddrMode_REL,
        .memoryAccess = ACCESS_REL,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x70] = bvs;

    // CLC
    CPU_Instruction clc = {
        .execute = &CPU_Instruction_CLC,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x18] = clc;

    // CLD
    CPU_Instruction cld = {
        .execute = &CPU_Instruction_CLD,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xD8] = cld;

    // CLI
    CPU_Instruction cli = {
        .execute = &CPU_Instruction_CLI,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x58] = cli;

    // CLV
    CPU_Instruction clv = {
        .execute = &CPU_Instruction_CLV,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xB8] = clv;

    // CMP
    CPU_Instruction cmpImm = {
        .execute = &CPU_Instruction_CMP,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xC9] = cmpImm;

    CPU_Instruction cmpZpg = {
        .execute = &CPU_Instruction_CMP,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0xC5] = cmpZpg;

    CPU_Instruction cmpZpx = {
        .execute = &CPU_Instruction_CMP,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xD5] = cmpZpx;

    CPU_Instruction cmpAbs = {
        .execute = &CPU_Instruction_CMP,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xCD] = cmpAbs;

    CPU_Instruction cmpAbsx = {
        .execute = &CPU_Instruction_CMP,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xDD] = cmpAbsx;

    CPU_Instruction cmpAbsy = {
        .execute = &CPU_Instruction_CMP,
        .addrModeExecute = &CPU_AddrMode_ABSY,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xD9] = cmpAbsy;

    CPU_Instruction cmpXind = {
        .execute = &CPU_Instruction_CMP,
        .addrModeExecute = &CPU_AddrMode_XIND,
        .memoryAccess = ACCESS_XIND_READ,
        .cycles = 6,
    };

    g_cpu.instructionTable[0xC1] = cmpXind;

    CPU_Instruction cmpIndy = {
        .execute = &CPU_Instruction_CMP,
        .addrModeExecute = &CPU_AddrMode_INDY,
        .memoryAccess = ACCESS_INDY_READ,
        .cycles = 5,
    };

    g_cpu.instructionTable[0xD1] = cmpIndy;

    // CPX
    CPU_Instruction cpxImm = {
        .execute = &CPU_Instruction_CPX,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xE0] = cpxImm;

    CPU_Instruction cpxZpg = {
        .execute = &CPU_Instruction_CPX,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0xE4] = cpxZpg;

    CPU_Instruction cpxAbs = {
        .execute = &CPU_Instruction_CPX,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xEC] = cpxAbs;

    // CPY
    CPU_Instruction cpyImm = {
        .execute = &CPU_Instruction_CPY,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xC0] = cpyImm;

    CPU_Instruction cpyZpg = {
        .execute = &CPU_Instruction_CPY,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0xC4] = cpyZpg;

    CPU_Instruction cpyAbs = {
        .execute = &CPU_Instruction_CPY,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xCC] = cpyAbs;

    // DEC
    CPU_Instruction decZpg = {
        .execute = &CPU_Instruction_DEC,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ_MODIFY_WRITE,
        .cycles = 5,
    };

    g_cpu.instructionTable[0xC6] = decZpg;

    CPU_Instruction decZpgx = {
        .execute = &CPU_Instruction_DEC,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPG_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0xD6] = decZpgx;

    CPU_Instruction decAbs = {
        .execute = &CPU_Instruction_DEC,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABSI_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0xCE] = decAbs;

    CPU_Instruction decAbsx = {
        .execute = &CPU_Instruction_DEC,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ_MODIFY_WRITE,
        .cycles = 7,
    };

    g_cpu.instructionTable[0xDE] = decAbsx;

    // DEX
    CPU_Instruction dex = {
        .execute = &CPU_Instruction_DEX,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xCA] = dex;

    // DEY
    CPU_Instruction dey = {
        .execute = &CPU_Instruction_DEY,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x88] = dey;

    // EOR
    CPU_Instruction eorImm = {
        .execute = &CPU_Instruction_EOR,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x49] = eorImm;

    CPU_Instruction eorZpg = {
        .execute = &CPU_Instruction_EOR,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x45] = eorZpg;

    CPU_Instruction eorZpgx = {
        .execute = &CPU_Instruction_EOR,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x55] = eorZpgx;

    CPU_Instruction eorAbs = {
        .execute = &CPU_Instruction_EOR,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ZPGI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x4D] = eorAbs;

    CPU_Instruction eorAbsx = {
        .execute = &CPU_Instruction_EOR,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x5D] = eorAbsx;

    CPU_Instruction eorAbsy = {
        .execute = &CPU_Instruction_EOR,
        .addrModeExecute = &CPU_AddrMode_ABSY,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x59] = eorAbsy;

    CPU_Instruction eorXind = {
        .execute = &CPU_Instruction_EOR,
        .addrModeExecute = &CPU_AddrMode_XIND,
        .memoryAccess = ACCESS_XIND_READ,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x41] = eorXind;

    CPU_Instruction eorIndy = {
        .execute = &CPU_Instruction_EOR,
        .addrModeExecute = &CPU_AddrMode_INDY,
        .memoryAccess = ACCESS_INDY_READ,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x51] = eorIndy;

    // INC
    CPU_Instruction incZpg = {
        .execute = &CPU_Instruction_INC,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ_MODIFY_WRITE,
        .cycles = 5,
    };

    g_cpu.instructionTable[0xE6] = incZpg;

    CPU_Instruction incZpgx = {
        .execute = &CPU_Instruction_INC,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0xF6] = incZpgx;

    CPU_Instruction incAbs = {
        .execute = &CPU_Instruction_INC,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0xEE] = incAbs;

    CPU_Instruction incAbsx = {
        .execute = &CPU_Instruction_INC,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ_MODIFY_WRITE,
        .cycles = 7,
    };

    g_cpu.instructionTable[0xFE] = incAbsx;

    // INX
    CPU_Instruction inx = {
        .execute = &CPU_Instruction_INX,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xE8] = inx;

    // INY
    CPU_Instruction iny = {
        .execute = &CPU_Instruction_INY,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xC8] = iny;

    // JMP
    CPU_Instruction jmpAbs = {
        .execute = &CPU_Instruction_JMP,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_JMP,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x4C] = jmpAbs;

    CPU_Instruction jmpInd = {
        .execute = &CPU_Instruction_JMP,
        .addrModeExecute = &CPU_AddrMode_IND,
        .memoryAccess = ACCESS_IND_JMP,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x6C] = jmpInd;

    // JSR
    CPU_Instruction jsr = {
        .execute = &CPU_Instruction_JSR,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_JSR,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x20] = jsr;

    // LDA
    CPU_Instruction ladImm = {
        .execute = &CPU_Instruction_LDA,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xA9] = ladImm;

    CPU_Instruction ldaZpg = {
        .execute = &CPU_Instruction_LDA,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0xA5] = ldaZpg;

    CPU_Instruction ldaZpgx = {
        .execute = &CPU_Instruction_LDA,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xB5] = ldaZpgx;

    CPU_Instruction ldaAbs = {
        .execute = &CPU_Instruction_LDA,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xAD] = ldaAbs;

    CPU_Instruction ldaAbsx = {
        .execute = &CPU_Instruction_LDA,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xBD] = ldaAbsx;

    CPU_Instruction ldaAbsy = {
        .execute = &CPU_Instruction_LDA,
        .addrModeExecute = &CPU_AddrMode_ABSY,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xB9] = ldaAbsy;

    CPU_Instruction ldaXind = {
        .execute = &CPU_Instruction_LDA,
        .addrModeExecute = &CPU_AddrMode_XIND,
        .memoryAccess = ACCESS_XIND_READ,
        .cycles = 6,
    };

    g_cpu.instructionTable[0xA1] = ldaXind;

    CPU_Instruction ldaIndy = {
        .execute = &CPU_Instruction_LDA,
        .addrModeExecute = &CPU_AddrMode_INDY,
        .memoryAccess = ACCESS_INDY_READ,
        .cycles = 5,
    };

    g_cpu.instructionTable[0xB1] = ldaIndy;

    // LDX
    CPU_Instruction ldxImm = {
        .execute = &CPU_Instruction_LDX,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xA2] = ldxImm;

    CPU_Instruction ldxZpg = {
        .execute = &CPU_Instruction_LDX,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0xA6] = ldxZpg;

    CPU_Instruction ldxZpgy = {
        .execute = &CPU_Instruction_LDX,
        .addrModeExecute = &CPU_AddrMode_ZPGY,
        .memoryAccess = ACCESS_ZPGI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xB6] = ldxZpgy;

    CPU_Instruction ldxAbs = {
        .execute = &CPU_Instruction_LDX,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xAE] = ldxAbs;

    CPU_Instruction ldxAbsy = {
        .execute = &CPU_Instruction_LDX,
        .addrModeExecute = &CPU_AddrMode_ABSY,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xBE] = ldxAbsy;

    // LDY
    CPU_Instruction ldyImm = {
        .execute = &CPU_Instruction_LDY,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xA0] = ldyImm;

    CPU_Instruction ldyZpg = {
        .execute = &CPU_Instruction_LDY,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0xA4] = ldyZpg;

    CPU_Instruction ldyZpgx = {
        .execute = &CPU_Instruction_LDY,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xB4] = ldyZpgx;

    CPU_Instruction ldyAbs = {
        .execute = &CPU_Instruction_LDY,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xAC] = ldyAbs;

    CPU_Instruction ldyAbsx = {
        .execute = &CPU_Instruction_LDY,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xBC] = ldyAbsx;

    // LSR
    CPU_Instruction lsrAcc = {
        .execute = &CPU_Instruction_LSR_ACC,
        .addrModeExecute = &CPU_AddrMode_ACC,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x4A] = lsrAcc;

    CPU_Instruction lsrZpg = {
        .execute = &CPU_Instruction_LSR,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ_MODIFY_WRITE,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x46] = lsrZpg;

    CPU_Instruction lsrZpgx = {
        .execute = &CPU_Instruction_LSR,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x56] = lsrZpgx;

    CPU_Instruction lsrAbs = {
        .execute = &CPU_Instruction_LSR,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x4E] = lsrAbs;

    CPU_Instruction lsrAbsx = {
        .execute = &CPU_Instruction_LSR,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ_MODIFY_WRITE,
        .cycles = 7,
    };

    g_cpu.instructionTable[0x5E] = lsrAbsx;

    // NOP
    CPU_Instruction nop = {
        .execute = &CPU_Instruction_NOP,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xEA] = nop;

    // ORA
    CPU_Instruction oraImm = {
        .execute = &CPU_Instruction_ORA,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x09] = oraImm;

    CPU_Instruction oraZpg = {
        .execute = &CPU_Instruction_ORA,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x05] = oraZpg;

    CPU_Instruction oraZpgx = {
        .execute = &CPU_Instruction_ORA,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x15] = oraZpgx;

    CPU_Instruction oraAbs = {
        .execute = &CPU_Instruction_ORA,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x0D] = oraAbs;

    CPU_Instruction oraAbsx = {
        .execute = &CPU_Instruction_ORA,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x1D] = oraAbsx;

    CPU_Instruction oraAbsy = {
        .execute = &CPU_Instruction_ORA,
        .addrModeExecute = &CPU_AddrMode_ABSY,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x19] = oraAbsy;

    CPU_Instruction oraXind = {
        .execute = &CPU_Instruction_ORA,
        .addrModeExecute = &CPU_AddrMode_XIND,
        .memoryAccess = ACCESS_XIND_READ,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x01] = oraXind;

    CPU_Instruction oraIndy = {
        .execute = &CPU_Instruction_ORA,
        .addrModeExecute = &CPU_AddrMode_INDY,
        .memoryAccess = ACCESS_INDY_READ,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x11] = oraIndy;

    // PHA
    CPU_Instruction pha = {
        .execute = &CPU_Instruction_PHA,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_PUSH,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x48] = pha;

    // PHP
    CPU_Instruction php = {
        .execute = &CPU_Instruction_PHP,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_PUSH,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x08] = php;

    // PLA
    CPU_Instruction pla = {
        .execute = &CPU_Instruction_PLA,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_PULL,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x68] = pla;

    // PLP
    CPU_Instruction plp = {
        .execute = &CPU_Instruction_PLP,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_PULL,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x28] = plp;

    // ROL
    CPU_Instruction rolAcc = {
        .execute = &CPU_Instruction_ROL_ACC,
        .addrModeExecute = &CPU_AddrMode_ACC,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x2A] = rolAcc;

    CPU_Instruction rolZpg = {
        .execute = &CPU_Instruction_ROL,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ_MODIFY_WRITE,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x26] = rolZpg;

    CPU_Instruction rolZpgx = {
        .execute = &CPU_Instruction_ROL,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x36] = rolZpgx;

    CPU_Instruction rolAbs = {
        .execute = &CPU_Instruction_ROL,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x2E] = rolAbs;

    CPU_Instruction rolAbsx = {
        .execute = &CPU_Instruction_ROL,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ_MODIFY_WRITE,
        .cycles = 7,
    };

    g_cpu.instructionTable[0x3E] = rolAbsx;

    // ROR
    CPU_Instruction rorAcc = {
        .execute = &CPU_Instruction_ROR_ACC,
        .addrModeExecute = &CPU_AddrMode_ACC,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x6A] = rorAcc;

    CPU_Instruction rorZpg = {
        .execute = &CPU_Instruction_ROR,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ_MODIFY_WRITE,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x66] = rorZpg;

    CPU_Instruction rorZpgx = {
        .execute = &CPU_Instruction_ROR,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPG_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x76] = rorZpgx;

    CPU_Instruction rorAbs = {
        .execute = &CPU_Instruction_ROR,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ_MODIFY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x6E] = rorAbs;

    CPU_Instruction rorAbsx = {
        .execute = &CPU_Instruction_ROR,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ_MODIFY_WRITE,
        .cycles = 7,
    };

    g_cpu.instructionTable[0x7E] = rorAbsx;

    // RTI
    CPU_Instruction rti = {
        .execute = &CPU_Instruction_RTI,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_RETURN,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x40] = rti;

    // RTS
    CPU_Instruction rts = {
        .execute = &CPU_Instruction_RTS,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_RETURN,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x60] = rts;

    // SBC
    CPU_Instruction sbcImm = {
        .execute = &CPU_Instruction_SBC,
        .addrModeExecute = &CPU_AddrMode_IMM,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xE9] = sbcImm;

    CPU_Instruction sbcZpg = {
        .execute = &CPU_Instruction_SBC,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_READ,
        .cycles = 3,
    };

    g_cpu.instructionTable[0xE5] = sbcZpg;

    CPU_Instruction sbcZpgx = {
        .execute = &CPU_Instruction_SBC,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xF5] = sbcZpgx;

    CPU_Instruction sbcAbs = {
        .execute = &CPU_Instruction_SBC,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xED] = sbcAbs;

    CPU_Instruction sbcAbsx = {
        .execute = &CPU_Instruction_SBC,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xFD] = sbcAbsx;

    CPU_Instruction sbcAbsy = {
        .execute = &CPU_Instruction_SBC,
        .addrModeExecute = &CPU_AddrMode_ABSY,
        .memoryAccess = ACCESS_ABSI_READ,
        .cycles = 4,
    };

    g_cpu.instructionTable[0xF9] = sbcAbsy;

    CPU_Instruction sbcXind = {
        .execute = &CPU_Instruction_SBC,
        .addrModeExecute = &CPU_AddrMode_XIND,
        .memoryAccess = ACCESS_XIND_READ,
        .cycles = 6,
    };

    g_cpu.instructionTable[0xE1] = sbcXind;

    CPU_Instruction sbcIndy = {
        .execute = &CPU_Instruction_SBC,
        .addrModeExecute = &CPU_AddrMode_INDY,
        .memoryAccess = ACCESS_INDY_READ,
        .cycles = 5,
    };

    g_cpu.instructionTable[0xF1] = sbcIndy;

    // SEC
    CPU_Instruction sec = {
        .execute = &CPU_Instruction_SEC,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x38] = sec;

    // SED
    CPU_Instruction sed = {
        .execute = &CPU_Instruction_SED,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xF8] = sed;

    // SEI
    CPU_Instruction sei = {
        .execute = &CPU_Instruction_SEI,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x78] = sei;

    // STA
    CPU_Instruction staZpg = {
        .execute = &CPU_Instruction_STA,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_WRITE,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x85] = staZpg;

    CPU_Instruction staZpgx = {
        .execute = &CPU_Instruction_STA,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_WRITE,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x95] = staZpgx;

    CPU_Instruction staAbs = {
        .execute = &CPU_Instruction_STA,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_WRITE,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x8D] = staAbs;

    CPU_Instruction staAbsx = {
        .execute = &CPU_Instruction_STA,
        .addrModeExecute = &CPU_AddrMode_ABSX,
        .memoryAccess = ACCESS_ABSI_WRITE,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x9D] = staAbsx;

    CPU_Instruction staAbsy = {
        .execute = &CPU_Instruction_STA,
        .addrModeExecute = &CPU_AddrMode_ABSY,
        .memoryAccess = ACCESS_ABSI_WRITE,
        .cycles = 5,
    };

    g_cpu.instructionTable[0x99] = staAbsy;

    CPU_Instruction staXind = {
        .execute = &CPU_Instruction_STA,
        .addrModeExecute = &CPU_AddrMode_XIND,
        .memoryAccess = ACCESS_XIND_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x81] = staXind;

    CPU_Instruction staIndy = {
        .execute = &CPU_Instruction_STA,
        .addrModeExecute = &CPU_AddrMode_INDY,
        .memoryAccess = ACCESS_INDY_WRITE,
        .cycles = 6,
    };

    g_cpu.instructionTable[0x91] = staIndy;

    // STX
    CPU_Instruction stxZpg = {
        .execute = &CPU_Instruction_STX,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_WRITE,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x86] = stxZpg;

    CPU_Instruction stxZpgy = {
        .execute = &CPU_Instruction_STX,
        .addrModeExecute = &CPU_AddrMode_ZPGY,
        .memoryAccess = ACCESS_ZPGI_WRITE,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x96] = stxZpgy;

    CPU_Instruction stxAbs = {
        .execute = &CPU_Instruction_STX,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_WRITE,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x8E] = stxAbs;

    // STY
    CPU_Instruction styZpg = {
        .execute = &CPU_Instruction_STY,
        .addrModeExecute = &CPU_AddrMode_ZPG,
        .memoryAccess = ACCESS_ZPG_WRITE,
        .cycles = 3,
    };

    g_cpu.instructionTable[0x84] = styZpg;

    CPU_Instruction styZpgx = {
        .execute = &CPU_Instruction_STY,
        .addrModeExecute = &CPU_AddrMode_ZPGX,
        .memoryAccess = ACCESS_ZPGI_WRITE,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x94] = styZpgx;

    CPU_Instruction styAbs = {
        .execute = &CPU_Instruction_STY,
        .addrModeExecute = &CPU_AddrMode_ABS,
        .memoryAccess = ACCESS_ABS_WRITE,
        .cycles = 4,
    };

    g_cpu.instructionTable[0x8C] = styAbs;

    // TAX
    CPU_Instruction tax = {
        .execute = &CPU_Instruction_TAX,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xAA] = tax;

    // TAY
    CPU_Instruction tay = {
        .execute = &CPU_Instruction_TAY,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xA8] = tay;

    // TSX
    CPU_Instruction tsx = {
        .execute = &CPU_Instruction_TSX,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0xBA] = tsx;

    // TXA
    CPU_Instruction txa = {
        .execute = &CPU_Instruction_TXA,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x8A] = txa;

    // TXS
    CPU_Instruction txs = {
        .execute = &CPU_Instruction_TXS,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x9A] = txs;

    // TYA
    CPU_Instruction tya = {
        .execute = &CPU_Instruction_TYA,
        .addrModeExecute = &CPU_AddrMode_IMPL,
        .memoryAccess = ACCESS_ACC_IMPL_IMM,
        .cycles = 2,
    };

    g_cpu.instructionTable[0x98] = tya;
}