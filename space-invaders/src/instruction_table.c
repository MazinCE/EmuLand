#include "cpu.h"

void CPU_CreateInstructionTable(void)
{
    Instruction nop = {
        .cycles_min = 1,
        .cycles_max = 1,
        .execute = &NOP,
    };

    g_cpu.instruction_table[0x00] = nop;

    Instruction lxib = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &LXIB,
    };

    g_cpu.instruction_table[0x01] = lxib;

    Instruction staxb = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &STAXB,
    };

    g_cpu.instruction_table[0x02] = staxb;

    Instruction inxb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INXB,
    };

    g_cpu.instruction_table[0x03] = inxb;

    Instruction inrb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INRB,
    };

    g_cpu.instruction_table[0x04] = inrb;

    Instruction dcrb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCRB,
    };

    g_cpu.instruction_table[0x05] = dcrb;

    Instruction mvib = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MVIB,
    };

    g_cpu.instruction_table[0x06] = mvib;

    Instruction rlc = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &RLC,
    };

    g_cpu.instruction_table[0x07] = rlc;

    Instruction dadb = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &DADB,
    };

    g_cpu.instruction_table[0x09] = dadb;

    Instruction ldaxb = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &LDAXB,
    };

    g_cpu.instruction_table[0x0A] = ldaxb;

    Instruction dcxb = {
      .cycles_min = 5,
      .cycles_max = 5,
      .execute = &DCXB,  
    };


    g_cpu.instruction_table[0x0B] = dcxb;

    // g_cpu.instruction_table[0x0C] = &INRC;
    // g_cpu.instruction_table[0x0D] = &DCRC;
    // g_cpu.instruction_table[0x0E] = &MVIC;
    // g_cpu.instruction_table[0x0F] = &RRC;
    // g_cpu.instruction_table[0x11] = &LXID;
    // g_cpu.instruction_table[0x12] = &STAXD;
    // g_cpu.instruction_table[0x13] = &INXD;
    // g_cpu.instruction_table[0x14] = &INRD;
    // g_cpu.instruction_table[0x15] = &DCRD;
    // g_cpu.instruction_table[0x16] = &MVID;
    // g_cpu.instruction_table[0x17] = &RAL;
    // g_cpu.instruction_table[0x19] = &DADD;
    // g_cpu.instruction_table[0x1A] = &LDAXD;
    // g_cpu.instruction_table[0x1B] = &DCXD;
    // g_cpu.instruction_table[0x1C] = &INRE;
    // g_cpu.instruction_table[0x1D] = &DCRE;
    // g_cpu.instruction_table[0x1E] = &MVIE;
    // g_cpu.instruction_table[0x1F] = &RAR;
    // g_cpu.instruction_table[0x21] = &LXIH;
    // g_cpu.instruction_table[0x22] = &SHLD;
    // g_cpu.instruction_table[0x23] = &INXH;
    // g_cpu.instruction_table[0x24] = &INRH;
    // g_cpu.instruction_table[0x25] = &DCRH;
    // g_cpu.instruction_table[0x26] = &MVIH;
    // g_cpu.instruction_table[0x27] = &DAA;
    // g_cpu.instruction_table[0x29] = &DADH;
    // g_cpu.instruction_table[0x2A] = &LHLD;
    // g_cpu.instruction_table[0x2B] = &DCXH;
    // g_cpu.instruction_table[0x2C] = &INRL;
    // g_cpu.instruction_table[0x2D] = &DCRL;
    // g_cpu.instruction_table[0x2E] = &MVIL;
    // g_cpu.instruction_table[0x2F] = &CMA;
    // g_cpu.instruction_table[0x31] = &LXISP;
    // g_cpu.instruction_table[0x32] = &STA;
    // g_cpu.instruction_table[0x33] = &INXSP;
    // g_cpu.instruction_table[0x34] = &INRM;
    // g_cpu.instruction_table[0x35] = &DCRM;
    // g_cpu.instruction_table[0x36] = &MVIM;
    // g_cpu.instruction_table[0x37] = &STC;
    // g_cpu.instruction_table[0x39] = &DADSP;
    // g_cpu.instruction_table[0x3A] = &LDA;
    // g_cpu.instruction_table[0x3B] = &DCXSP;
    // g_cpu.instruction_table[0x3C] = &INRA;
    // g_cpu.instruction_table[0x3D] = &DCRA;
    // g_cpu.instruction_table[0x3E] = &MVIA;
    // g_cpu.instruction_table[0x3F] = &CMC;
    // g_cpu.instruction_table[0x40] = &MOVBB;
    // g_cpu.instruction_table[0x41] = &MOVBC;
    // g_cpu.instruction_table[0x42] = &MOVBD;
    // g_cpu.instruction_table[0x43] = &MOVBE;
    // g_cpu.instruction_table[0x44] = &MOVBH;
    // g_cpu.instruction_table[0x45] = &MOVBL;
    // g_cpu.instruction_table[0x46] = &MOVBM;
    // g_cpu.instruction_table[0x47] = &MOVBA;
    // g_cpu.instruction_table[0x48] = &MOVCB;
    // g_cpu.instruction_table[0x49] = &MOVCC;
    // g_cpu.instruction_table[0x4A] = &MOVCD;
    // g_cpu.instruction_table[0x4B] = &MOVCE;
    // g_cpu.instruction_table[0x4C] = &MOVCH;
    // g_cpu.instruction_table[0x4D] = &MOVCL;
    // g_cpu.instruction_table[0x4E] = &MOVCM;
    // g_cpu.instruction_table[0x4F] = &MOVCA;
    // g_cpu.instruction_table[0x50] = &MOVDB;
    // g_cpu.instruction_table[0x51] = &MOVDC;
    // g_cpu.instruction_table[0x52] = &MOVDD;
    // g_cpu.instruction_table[0x53] = &MOVDE;
    // g_cpu.instruction_table[0x54] = &MOVDH;
    // g_cpu.instruction_table[0x55] = &MOVDL;
    // g_cpu.instruction_table[0x56] = &MOVDM;
    // g_cpu.instruction_table[0x57] = &MOVDA;
    // g_cpu.instruction_table[0x58] = &MOVEB;
    // g_cpu.instruction_table[0x59] = &MOVEC;
    // g_cpu.instruction_table[0x5A] = &MOVED;
    // g_cpu.instruction_table[0x5B] = &MOVEE;
    // g_cpu.instruction_table[0x5C] = &MOVEH;
    // g_cpu.instruction_table[0x5D] = &MOVEL;
    // g_cpu.instruction_table[0x5E] = &MOVEM;
    // g_cpu.instruction_table[0x5F] = &MOVEA;
    // g_cpu.instruction_table[0x60] = &MOVHB;
    // g_cpu.instruction_table[0x61] = &MOVHC;
    // g_cpu.instruction_table[0x62] = &MOVHD;
    // g_cpu.instruction_table[0x63] = &MOVHE;
    // g_cpu.instruction_table[0x64] = &MOVHH;
    // g_cpu.instruction_table[0x65] = &MOVHL;
    // g_cpu.instruction_table[0x66] = &MOVHM;
    // g_cpu.instruction_table[0x67] = &MOVHA;
    // g_cpu.instruction_table[0x68] = &MOVLB;
    // g_cpu.instruction_table[0x69] = &MOVLC;
    // g_cpu.instruction_table[0x6A] = &MOVLD;
    // g_cpu.instruction_table[0x6B] = &MOVLE;
    // g_cpu.instruction_table[0x6C] = &MOVLH;
    // g_cpu.instruction_table[0x6D] = &MOVLL;
    // g_cpu.instruction_table[0x6E] = &MOVLM;
    // g_cpu.instruction_table[0x6F] = &MOVLA;
    // g_cpu.instruction_table[0x70] = &MOVMB;
    // g_cpu.instruction_table[0x71] = &MOVMC;
    // g_cpu.instruction_table[0x72] = &MOVMD;
    // g_cpu.instruction_table[0x73] = &MOVME;
    // g_cpu.instruction_table[0x74] = &MOVMH;
    // g_cpu.instruction_table[0x75] = &MOVML;
    // g_cpu.instruction_table[0x76] = &HLT;
    // g_cpu.instruction_table[0x77] = &MOVMA;
    // g_cpu.instruction_table[0x78] = &MOVAB;
    // g_cpu.instruction_table[0x79] = &MOVAC;
    // g_cpu.instruction_table[0x7A] = &MOVAD;
    // g_cpu.instruction_table[0x7B] = &MOVAE;
    // g_cpu.instruction_table[0x7C] = &MOVAH;
    // g_cpu.instruction_table[0x7D] = &MOVAL;
    // g_cpu.instruction_table[0x7E] = &MOVAM;
    // g_cpu.instruction_table[0x7F] = &MOVAA;
    // g_cpu.instruction_table[0x80] = &ADDB;
    // g_cpu.instruction_table[0x81] = &ADDC;
    // g_cpu.instruction_table[0x82] = &ADDD;
    // g_cpu.instruction_table[0x83] = &ADDE;
    // g_cpu.instruction_table[0x84] = &ADDH;
    // g_cpu.instruction_table[0x85] = &ADDL;
    // g_cpu.instruction_table[0x86] = &ADDM;
    // g_cpu.instruction_table[0x87] = &ADDA;
    // g_cpu.instruction_table[0x88] = &ADCB;
    // g_cpu.instruction_table[0x89] = &ADCC;
    // g_cpu.instruction_table[0x8A] = &ADCD;
    // g_cpu.instruction_table[0x8B] = &ADCE;
    // g_cpu.instruction_table[0x8C] = &ADCH;
    // g_cpu.instruction_table[0x8D] = &ADCL;
    // g_cpu.instruction_table[0x8E] = &ADCM;
    // g_cpu.instruction_table[0x8F] = &ADCA;
    // g_cpu.instruction_table[0x90] = &SUBB;
    // g_cpu.instruction_table[0x91] = &SUBC;
    // g_cpu.instruction_table[0x92] = &SUBD;
    // g_cpu.instruction_table[0x93] = &SUBE;
    // g_cpu.instruction_table[0x94] = &SUBH;
    // g_cpu.instruction_table[0x95] = &SUBL;
    // g_cpu.instruction_table[0x96] = &SUBM;
    // g_cpu.instruction_table[0x97] = &SUBA;
    // g_cpu.instruction_table[0x98] = &SBBB;
    // g_cpu.instruction_table[0x99] = &SBBC;
    // g_cpu.instruction_table[0x9A] = &SBBD;
    // g_cpu.instruction_table[0x9B] = &SBBE;
    // g_cpu.instruction_table[0x9C] = &SBBH;
    // g_cpu.instruction_table[0x9D] = &SBBL;
    // g_cpu.instruction_table[0x9E] = &SBBM;
    // g_cpu.instruction_table[0x9F] = &SBBA;
    // g_cpu.instruction_table[0xA0] = &ANAB;
    // g_cpu.instruction_table[0xA1] = &ANAC;
    // g_cpu.instruction_table[0xA2] = &ANAD;
    // g_cpu.instruction_table[0xA3] = &ANAE;
    // g_cpu.instruction_table[0xA4] = &ANAH;
    // g_cpu.instruction_table[0xA5] = &ANAL;
    // g_cpu.instruction_table[0xA6] = &ANAM;
    // g_cpu.instruction_table[0xA7] = &ANAA;
    // g_cpu.instruction_table[0xA8] = &XRAB;
    // g_cpu.instruction_table[0xA9] = &XRAC;
    // g_cpu.instruction_table[0xAA] = &XRAD;
    // g_cpu.instruction_table[0xAB] = &XRAE;
    // g_cpu.instruction_table[0xAC] = &XRAH;
    // g_cpu.instruction_table[0xAD] = &XRAL;
    // g_cpu.instruction_table[0xAE] = &XRAM;
    // g_cpu.instruction_table[0xAF] = &XRAA;
    // g_cpu.instruction_table[0xB0] = &ORAB;
    // g_cpu.instruction_table[0xB1] = &ORAC;
    // g_cpu.instruction_table[0xB2] = &ORAD;
    // g_cpu.instruction_table[0xB3] = &ORAE;
    // g_cpu.instruction_table[0xB4] = &ORAH;
    // g_cpu.instruction_table[0xB5] = &ORAL;
    // g_cpu.instruction_table[0xB6] = &ORAM;
    // g_cpu.instruction_table[0xB7] = &ORAA;
    // g_cpu.instruction_table[0xB8] = &CMPB;
    // g_cpu.instruction_table[0xB9] = &CMPC;
    // g_cpu.instruction_table[0xBA] = &CMPD;
    // g_cpu.instruction_table[0xBB] = &CMPE;
    // g_cpu.instruction_table[0xBC] = &CMPH;
    // g_cpu.instruction_table[0xBD] = &CMPL;
    // g_cpu.instruction_table[0xBE] = &CMPM;
    // g_cpu.instruction_table[0xBF] = &CMPA;
    // g_cpu.instruction_table[0xC0] = &RNZ;
    // g_cpu.instruction_table[0xC1] = &POPB;
    // g_cpu.instruction_table[0xC2] = &JNZ;
    // g_cpu.instruction_table[0xC3] = &JMP;
    // g_cpu.instruction_table[0xC4] = &CNZ;
    // g_cpu.instruction_table[0xC5] = &PUSHB;
    // g_cpu.instruction_table[0xC6] = &ADI;
    // g_cpu.instruction_table[0xC8] = &RZ;
    // g_cpu.instruction_table[0xC9] = &RET;
    // g_cpu.instruction_table[0xCA] = &JZ;
    // g_cpu.instruction_table[0xCC] = &CZ;
    // g_cpu.instruction_table[0xCD] = &CALL;
    // g_cpu.instruction_table[0xCE] = &ACI;
    // g_cpu.instruction_table[0xD0] = &RNC;
    // g_cpu.instruction_table[0xD1] = &POPD;
    // g_cpu.instruction_table[0xD2] = &JNC;
    // g_cpu.instruction_table[0xD3] = &OUT;
    // g_cpu.instruction_table[0xD4] = &CNC;
    // g_cpu.instruction_table[0xD5] = &PUSHD;
    // g_cpu.instruction_table[0xD6] = &SUI;
    // g_cpu.instruction_table[0xD8] = &RC;
    // g_cpu.instruction_table[0xDA] = &JC;
    // g_cpu.instruction_table[0xDB] = &IN;
    // g_cpu.instruction_table[0xDC] = &CC;
    // g_cpu.instruction_table[0xDE] = &SBI;
    // g_cpu.instruction_table[0xE0] = &RPO;
    // g_cpu.instruction_table[0xE1] = &POPH;
    // g_cpu.instruction_table[0xE2] = &JPO;
    // g_cpu.instruction_table[0xE3] = &XTHL;
    // g_cpu.instruction_table[0xE4] = &CPO;
    // g_cpu.instruction_table[0xE5] = &PUSHH;
    // g_cpu.instruction_table[0xE6] = &ANI;
    // g_cpu.instruction_table[0xE8] = &RPE;
    // g_cpu.instruction_table[0xE9] = &PCHL;
    // g_cpu.instruction_table[0xEA] = &JPE;
    // g_cpu.instruction_table[0xEB] = &XCHG;
    // g_cpu.instruction_table[0xEC] = &CPE;
    // g_cpu.instruction_table[0xEE] = &XRI;
    // g_cpu.instruction_table[0xF0] = &RP;
    // g_cpu.instruction_table[0xF1] = &POPPSW;
    // g_cpu.instruction_table[0xF2] = &JP;
    // g_cpu.instruction_table[0xF3] = &DI;
    // g_cpu.instruction_table[0xF4] = &CP;
    // g_cpu.instruction_table[0xF5] = &PUSHPSW;
    // g_cpu.instruction_table[0xF6] = &ORI;
    // g_cpu.instruction_table[0xF8] = &RM;
    // g_cpu.instruction_table[0xF9] = &SPHL;
    // g_cpu.instruction_table[0xFA] = &JM;
    // g_cpu.instruction_table[0xFB] = &EI;
    // g_cpu.instruction_table[0xFC] = &CM;
    // g_cpu.instruction_table[0xFE] = &CPI;
}