#include "cpu.h"

void CPU_CreateInstructionTable(void)
{
    Instruction nop = {
        .cycles_min = 1,
        .cycles_max = 1,
        .execute = &NOP,
    };

    Instruction lxib = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &LXIB,
    };

    Instruction staxb = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &STAXB,
    };

    Instruction inxb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INXB,
    };

    Instruction inrb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INRB,
    };

    Instruction dcrb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCRB,
    };

    Instruction mvib = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MVIB,
    };

    Instruction rlc = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &RLC,
    };

    Instruction dadb = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &DADB,
    };

    Instruction ldaxb = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &LDAXB,
    };

    Instruction dcxb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCXB,
    };

    Instruction inrc = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INRC,
    };

    Instruction dcrc = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCRC,
    };

    Instruction mvic = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MVIC,
    };

    Instruction rrc = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &RRC,
    };

    Instruction lxid = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &LXID,
    };

    Instruction staxd = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &STAXD,
    };

    Instruction inxd = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INXD,
    };

    Instruction inrd = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INRD,
    };

    Instruction dcrd = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCRD,
    };

    Instruction mvid = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MVID,
    };

    Instruction ral = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &RAL,
    };

    Instruction dadd = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &DADD,
    };

    Instruction ldaxd = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &LDAXD,
    };

    Instruction dcxd = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCXD,
    };

    Instruction inre = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INRE,
    };

    Instruction dcre = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCRE,
    };

    Instruction mvie = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MVIE,
    };

    Instruction rar = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &RAR,
    };

    Instruction lxih = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &LXIH,
    };

    Instruction shld = {
        .cycles_min = 16,
        .cycles_max = 16,
        .execute = &SHLD,
    };

    Instruction inxh = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INXH,
    };

    Instruction inrh = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INRH,
    };

    Instruction dcrh = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCRH,
    };

    Instruction mvih = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MVIH,
    };

    Instruction daa = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &DAA,
    };

    Instruction dadh = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &DADH};

    Instruction lhld = {
        .cycles_min = 16,
        .cycles_max = 16,
        .execute = &LHLD,
    };

    Instruction dcxh = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCXH,
    };

    Instruction inrl = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INRL,
    };

    Instruction dcrl = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCRL,
    };

    Instruction mvil = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MVIL,
    };

    Instruction cma = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &CMA,
    };

    Instruction lxisp = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &LXISP,
    };

    Instruction sta = {
        .cycles_min = 13,
        .cycles_max = 13,
        .execute = &STA,
    };

    Instruction inxsp = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INXSP,
    };

    Instruction inrm = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &INRM,
    };

    Instruction dcrm = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &DCRM,
    };

    Instruction mvim = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &MVIM,
    };

    Instruction stc = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &STC,
    };

    Instruction dadsp = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &DADSP,
    };

    Instruction lda = {
        .cycles_min = 13,
        .cycles_max = 13,
        .execute = &LDA,
    };

    Instruction dcxsp = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCXSP,
    };

    Instruction inra = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &INRA,
    };

    Instruction dcra = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &DCRA,
    };

    Instruction mvia = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MVIA,
    };

    Instruction cmc = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &CMC,
    };

    Instruction movbb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVBB,
    };

    Instruction movbc = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVBC,
    };

    Instruction movbd = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVBD,
    };

    Instruction movbe = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVBE,
    };

    Instruction movbh = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVBH,
    };

    Instruction movbl = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVBL,
    };

    Instruction movbm = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVBM,
    };

    Instruction movba = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVBA,
    };

    Instruction movcb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVCB,
    };

    Instruction movcc = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVCC,
    };

    Instruction movcd = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVCD,
    };

    Instruction movce = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVCE,
    };

    Instruction movch = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVCH,
    };

    Instruction movcl = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVCL,
    };

    Instruction movcm = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVCM,
    };

    Instruction movca = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVCA,
    };

    Instruction movdb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVDB,
    };

    Instruction movdc = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVDC,
    };

    Instruction movdd = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVDD,
    };

    Instruction movde = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVDE,
    };

    Instruction movdh = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVDH,
    };

    Instruction movdl = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVDL,
    };

    Instruction movdm = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVDM,
    };

    Instruction movda = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVDA,
    };

    Instruction moveb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVEB,
    };

    Instruction movec = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVEC,
    };

    Instruction moved = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVED,
    };

    Instruction movee = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVEE,
    };

    Instruction moveh = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVEH,
    };

    Instruction movel = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVEL,
    };

    Instruction movem = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVEM,
    };

    Instruction movea = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVEA,
    };

    Instruction movhb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVHB,
    };

    Instruction movhc = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVHC,
    };

    Instruction movhd = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVHD,
    };

    Instruction movhe = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVHE,
    };

    Instruction movhh = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVHH,
    };

    Instruction movhl = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVHL,
    };

    Instruction movhm = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVHM,
    };

    Instruction movha = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVHA,
    };

    Instruction movlb = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVLB,
    };

    Instruction movlc = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVLC,
    };

    Instruction movld = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVLD,
    };

    Instruction movle = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVLE,
    };

    Instruction movlh = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVLH,
    };

    Instruction movll = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVLL,
    };

    Instruction movlm = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVLM,
    };

    Instruction movla = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVLA,
    };

    Instruction movmb = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVMB,
    };

    Instruction movmc = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVMC,
    };

    Instruction movmd = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVMD,
    };

    Instruction movme = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVME,
    };

    Instruction movmh = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVMH,
    };

    Instruction movml = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVML,
    };

    Instruction hlt = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &HLT,
    };

    Instruction movma = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVMA,
    };

    Instruction movab = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVAB,
    };

    Instruction movac = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVAC,
    };

    Instruction movad = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVAD,
    };

    Instruction movae = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVAE,
    };

    Instruction movah = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVAH,
    };

    Instruction moval = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVAL,
    };

    Instruction movam = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &MOVAM,
    };

    Instruction movaa = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &MOVAA,
    };

    Instruction addb = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADDB,
    };

    Instruction addc = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADDC,
    };

    Instruction addd = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADDD,
    };

    Instruction adde = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADDE,
    };

    Instruction addh = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADDH,
    };

    Instruction addl = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADDL,
    };

    Instruction addm = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &ADDM,
    };

    Instruction adda = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADDA,
    };

    Instruction adcb = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADCB,
    };

    Instruction adcc = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADCC,
    };

    Instruction adcd = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADCD,
    };

    Instruction adce = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADCE,
    };

    Instruction adch = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADCH,
    };

    Instruction adcl = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADCL,
    };

    Instruction adcm = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &ADCM,
    };

    Instruction adca = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ADCA,
    };

    Instruction subb = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SUBB,
    };

    Instruction subc = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SUBC,
    };

    Instruction subd = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SUBD,
    };

    Instruction sube = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SUBE,
    };

    Instruction subh = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SUBH,
    };

    Instruction subl = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SUBL,
    };

    Instruction subm = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &SUBM,
    };

    Instruction suba = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SUBA,
    };

    Instruction sbbb = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SBBB,
    };

    Instruction sbbc = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SBBC,
    };

    Instruction sbbd = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SBBD,
    };

    Instruction sbbe = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SBBE,
    };

    Instruction sbbh = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SBBH,
    };

    Instruction sbbl = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SBBL,
    };

    Instruction sbbm = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &SBBM,
    };

    Instruction sbba = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &SBBA,
    };

    Instruction anab = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ANAB,
    };

    Instruction anac = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ANAC,
    };

    Instruction anad = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ANAD,
    };

    Instruction anae = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ANAE,
    };

    Instruction anah = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ANAH,
    };

    Instruction anal = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ANAL,
    };

    Instruction anam = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &ANAM,
    };

    Instruction anaa = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ANAA,
    };

    Instruction xrab = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &XRAB,
    };

    Instruction xrac = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &XRAC,
    };

    Instruction xrad = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &XRAD,
    };

    Instruction xrae = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &XRAE,
    };

    Instruction xrah = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &XRAH,
    };

    Instruction xral = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &XRAL,
    };

    Instruction xram = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &XRAM,
    };

    Instruction xraa = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &XRAA,
    };

    Instruction orab = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ORAB,
    };

    Instruction orac = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ORAC,
    };

    Instruction orad = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ORAD,
    };

    Instruction orae = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ORAE,
    };

    Instruction orah = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ORAH,
    };

    Instruction oral = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ORAL,
    };

    Instruction oram = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &ORAM,
    };

    Instruction oraa = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ORAA,
    };

    Instruction cmpb = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &CMPB,
    };

    Instruction cmpc = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &CMPC,
    };

    Instruction cmpd = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &CMPD,
    };

    Instruction cmpe = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &CMPE,
    };

    Instruction cmph = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &CMPH,
    };

    Instruction cmpl = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &CMPL,
    };

    Instruction cmpm = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &CMPM,
    };

    Instruction cmpa = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &CMPA,
    };

    Instruction rnz = {
        .cycles_min = 5,
        .cycles_max = 11,
        .execute = &RNZ,
    };

    Instruction popb = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &POPB,
    };

    Instruction jnz = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &JNZ,
    };

    Instruction jmp = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &JMP,
    };

    Instruction cnz = {
        .cycles_min = 11,
        .cycles_max = 17,
        .execute = &CNZ,
    };

    Instruction pushb = {
        .cycles_min = 11,
        .cycles_max = 11,
        .execute = &PUSHB,
    };

    Instruction adi = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &ADI,
    };

    Instruction rz = {
        .cycles_min = 5,
        .cycles_max = 11,
        .execute = &RZ,
    };

    Instruction ret = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &RET,
    };

    Instruction jz = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &JZ,
    };

    Instruction cz = {
        .cycles_min = 11,
        .cycles_max = 17,
        .execute = &CZ,
    };

    Instruction call = {
        .cycles_min = 17,
        .cycles_max = 17,
        .execute = &CALL,
    };

    Instruction aci = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &ACI,
    };

    Instruction rnc = {
        .cycles_min = 5,
        .cycles_max = 11,
        .execute = &RNC,
    };

    Instruction popd = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &POPD,
    };

    Instruction jnc = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &JNC,
    };

    Instruction out = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &OUT,
    };

    Instruction cnc = {
        .cycles_min = 11,
        .cycles_max = 17,
        .execute = &CNC,
    };

    Instruction pushd = {
        .cycles_min = 11,
        .cycles_max = 11,
        .execute = &PUSHD,
    };

    Instruction sui = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &SUI,
    };

    Instruction rc = {
        .cycles_min = 5,
        .cycles_max = 11,
        .execute = &RC,
    };

    Instruction jc = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &JC,
    };

    Instruction in = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &IN,
    };

    Instruction cc = {
        .cycles_min = 11,
        .cycles_max = 17,
        .execute = &CC,
    };

    Instruction sbi = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &SBI,
    };

    Instruction rpo = {
        .cycles_min = 5,
        .cycles_max = 11,
        .execute = &RPO,
    };

    Instruction poph = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &POPH,
    };

    Instruction jpo = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &JPO,
    };

    Instruction xthl = {
        .cycles_min = 18,
        .cycles_max = 18,
        .execute = &XTHL,
    };

    Instruction cpo = {
        .cycles_min = 11,
        .cycles_max = 17,
        .execute = &CPO,
    };

    Instruction pushh = {
        .cycles_min = 11,
        .cycles_max = 11,
        .execute = &PUSHH,
    };

    Instruction ani = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &ANI,
    };

    Instruction rpe = {
        .cycles_min = 5,
        .cycles_max = 11,
        .execute = &RPE,
    };

    Instruction pchl = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &PCHL,
    };

    Instruction jpe = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &JPE,
    };

    Instruction xchg = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &XCHG,
    };

    Instruction cpe = {
        .cycles_min = 11,
        .cycles_max = 17,
        .execute = &CPE,
    };

    Instruction xri = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &XRI,
    };

    Instruction rp = {
        .cycles_min = 5,
        .cycles_max = 11,
        .execute = &RP,
    };

    Instruction poppsw = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &POPPSW,
    };

    Instruction jp = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &JP,
    };

    Instruction di = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &DI,
    };

    Instruction cp = {
        .cycles_min = 11,
        .cycles_max = 17,
        .execute = &CP,
    };

    Instruction pushpsw = {
        .cycles_min = 11,
        .cycles_max = 11,
        .execute = &PUSHPSW,
    };

    Instruction ori = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &ORI,
    };

    Instruction rm = {
        .cycles_min = 5,
        .cycles_max = 11,
        .execute = &RM,
    };

    Instruction sphl = {
        .cycles_min = 5,
        .cycles_max = 5,
        .execute = &SPHL,
    };

    Instruction jm = {
        .cycles_min = 10,
        .cycles_max = 10,
        .execute = &JM,
    };

    Instruction ei = {
        .cycles_min = 4,
        .cycles_max = 4,
        .execute = &EI,
    };

    Instruction cm = {
        .cycles_min =11,
        .cycles_max =17 ,
        .execute = &CM,
    };

    Instruction cpi = {
        .cycles_min = 7,
        .cycles_max = 7,
        .execute = &CPI,
    };

    g_cpu.instruction_table[0x00] = nop;
    g_cpu.instruction_table[0x01] = lxib;
    g_cpu.instruction_table[0x02] = staxb;
    g_cpu.instruction_table[0x03] = inxb;
    g_cpu.instruction_table[0x04] = inrb;
    g_cpu.instruction_table[0x05] = dcrb;
    g_cpu.instruction_table[0x06] = mvib;
    g_cpu.instruction_table[0x07] = rlc;
    g_cpu.instruction_table[0x09] = dadb;
    g_cpu.instruction_table[0x0A] = ldaxb;
    g_cpu.instruction_table[0x0B] = dcxb;
    g_cpu.instruction_table[0x0C] = inrc;
    g_cpu.instruction_table[0x0D] = dcrc;
    g_cpu.instruction_table[0x0E] = mvic;
    g_cpu.instruction_table[0x0F] = rrc;
    g_cpu.instruction_table[0x11] = lxid;
    g_cpu.instruction_table[0x12] = staxd;
    g_cpu.instruction_table[0x13] = inxd;
    g_cpu.instruction_table[0x14] = inrd;
    g_cpu.instruction_table[0x15] = dcrd;
    g_cpu.instruction_table[0x16] = mvid;
    g_cpu.instruction_table[0x17] = ral;
    g_cpu.instruction_table[0x19] = dadd;
    g_cpu.instruction_table[0x1A] = ldaxd;
    g_cpu.instruction_table[0x1B] = dcxd;
    g_cpu.instruction_table[0x1C] = inre;
    g_cpu.instruction_table[0x1D] = dcre;
    g_cpu.instruction_table[0x1E] = mvie;
    g_cpu.instruction_table[0x1F] = rar;
    g_cpu.instruction_table[0x21] = lxih;
    g_cpu.instruction_table[0x22] = shld;
    g_cpu.instruction_table[0x23] = inxh;
    g_cpu.instruction_table[0x24] = inrh;
    g_cpu.instruction_table[0x25] = dcrh;
    g_cpu.instruction_table[0x26] = mvih;
    g_cpu.instruction_table[0x27] = daa;
    g_cpu.instruction_table[0x29] = dadh;
    g_cpu.instruction_table[0x2A] = lhld;
    g_cpu.instruction_table[0x2B] = dcxh;
    g_cpu.instruction_table[0x2C] = inrl;
    g_cpu.instruction_table[0x2D] = dcrl;
    g_cpu.instruction_table[0x2E] = mvil;
    g_cpu.instruction_table[0x2F] = cma;
    g_cpu.instruction_table[0x31] = lxisp;
    g_cpu.instruction_table[0x32] = sta;
    g_cpu.instruction_table[0x33] = inxsp;
    g_cpu.instruction_table[0x34] = inrm;
    g_cpu.instruction_table[0x35] = dcrm;
    g_cpu.instruction_table[0x36] = mvim;
    g_cpu.instruction_table[0x37] = stc;
    g_cpu.instruction_table[0x39] = dadsp;
    g_cpu.instruction_table[0x3A] = lda;
    g_cpu.instruction_table[0x3B] = dcxsp;
    g_cpu.instruction_table[0x3C] = inra;
    g_cpu.instruction_table[0x3D] = dcra;
    g_cpu.instruction_table[0x3E] = mvia;
    g_cpu.instruction_table[0x3F] = cmc;
    g_cpu.instruction_table[0x40] = movbb;
    g_cpu.instruction_table[0x41] = movbc;
    g_cpu.instruction_table[0x42] = movbd;
    g_cpu.instruction_table[0x43] = movbe;
    g_cpu.instruction_table[0x44] = movbh;
    g_cpu.instruction_table[0x45] = movbl;
    g_cpu.instruction_table[0x46] = movbm;
    g_cpu.instruction_table[0x47] = movba;
    g_cpu.instruction_table[0x48] = movcb;
    g_cpu.instruction_table[0x49] = movcc;
    g_cpu.instruction_table[0x4A] = movcd;
    g_cpu.instruction_table[0x4B] = movce;
    g_cpu.instruction_table[0x4C] = movch;
    g_cpu.instruction_table[0x4D] = movcl;
    g_cpu.instruction_table[0x4E] = movcm;
    g_cpu.instruction_table[0x4F] = movca;
    g_cpu.instruction_table[0x50] = movdb;
    g_cpu.instruction_table[0x51] = movdc;
    g_cpu.instruction_table[0x52] = movdd;
    g_cpu.instruction_table[0x53] = movde;
    g_cpu.instruction_table[0x54] = movdh;
    g_cpu.instruction_table[0x55] = movdl;
    g_cpu.instruction_table[0x56] = movdm;
    g_cpu.instruction_table[0x57] = movda;
    g_cpu.instruction_table[0x58] = moveb;
    g_cpu.instruction_table[0x59] = movec;
    g_cpu.instruction_table[0x5A] = moved;
    g_cpu.instruction_table[0x5B] = movee;
    g_cpu.instruction_table[0x5C] = moveh;
    g_cpu.instruction_table[0x5D] = movel;
    g_cpu.instruction_table[0x5E] = movem;
    g_cpu.instruction_table[0x5F] = movea;
    g_cpu.instruction_table[0x60] = movhb;
    g_cpu.instruction_table[0x61] = movhc;
    g_cpu.instruction_table[0x62] = movhd;
    g_cpu.instruction_table[0x63] = movhe;
    g_cpu.instruction_table[0x64] = movhh;
    g_cpu.instruction_table[0x65] = movhl;
    g_cpu.instruction_table[0x66] = movhm;
    g_cpu.instruction_table[0x67] = movha;
    g_cpu.instruction_table[0x68] = movlb;
    g_cpu.instruction_table[0x69] = movlc;
    g_cpu.instruction_table[0x6A] = movld;
    g_cpu.instruction_table[0x6B] = movle;
    g_cpu.instruction_table[0x6C] = movlh;
    g_cpu.instruction_table[0x6D] = movll;
    g_cpu.instruction_table[0x6E] = movlm;
    g_cpu.instruction_table[0x6F] = movla;
    g_cpu.instruction_table[0x70] = movmb;
    g_cpu.instruction_table[0x71] = movmc;
    g_cpu.instruction_table[0x72] = movmd;
    g_cpu.instruction_table[0x73] = movme;
    g_cpu.instruction_table[0x74] = movmh;
    g_cpu.instruction_table[0x75] = movml;
    g_cpu.instruction_table[0x76] = hlt;
    g_cpu.instruction_table[0x77] = movma;
    g_cpu.instruction_table[0x78] = movab;
    g_cpu.instruction_table[0x79] = movac;
    g_cpu.instruction_table[0x7A] = movad;
    g_cpu.instruction_table[0x7B] = movae;
    g_cpu.instruction_table[0x7C] = movah;
    g_cpu.instruction_table[0x7D] = moval;
    g_cpu.instruction_table[0x7E] = movam;
    g_cpu.instruction_table[0x7F] = movaa;
    g_cpu.instruction_table[0x80] = addb;
    g_cpu.instruction_table[0x81] = addc;
    g_cpu.instruction_table[0x82] = addd;
    g_cpu.instruction_table[0x83] = adde;
    g_cpu.instruction_table[0x84] = addh;
    g_cpu.instruction_table[0x85] = addl;
    g_cpu.instruction_table[0x86] = addm;
    g_cpu.instruction_table[0x87] = adda;
    g_cpu.instruction_table[0x88] = adcb;
    g_cpu.instruction_table[0x89] = adcc;
    g_cpu.instruction_table[0x8A] = adcd;
    g_cpu.instruction_table[0x8B] = adce;
    g_cpu.instruction_table[0x8C] = adch;
    g_cpu.instruction_table[0x8D] = adcl;
    g_cpu.instruction_table[0x8E] = adcm;
    g_cpu.instruction_table[0x8F] = adca;
    g_cpu.instruction_table[0x90] = subb;
    g_cpu.instruction_table[0x91] = subc;
    g_cpu.instruction_table[0x92] = subd;
    g_cpu.instruction_table[0x93] = sube;
    g_cpu.instruction_table[0x94] = subh;
    g_cpu.instruction_table[0x95] = subl;
    g_cpu.instruction_table[0x96] = subm;
    g_cpu.instruction_table[0x97] = suba;
    g_cpu.instruction_table[0x98] = sbbb;
    g_cpu.instruction_table[0x99] = sbbc;
    g_cpu.instruction_table[0x9A] = sbbd;
    g_cpu.instruction_table[0x9B] = sbbe;
    g_cpu.instruction_table[0x9C] = sbbh;
    g_cpu.instruction_table[0x9D] = sbbl;
    g_cpu.instruction_table[0x9E] = sbbm;
    g_cpu.instruction_table[0x9F] = sbba;
    g_cpu.instruction_table[0xA0] = anab;
    g_cpu.instruction_table[0xA1] = anac;
    g_cpu.instruction_table[0xA2] = anad;
    g_cpu.instruction_table[0xA3] = anae;
    g_cpu.instruction_table[0xA4] = anah;
    g_cpu.instruction_table[0xA5] = anal;
    g_cpu.instruction_table[0xA6] = anam;
    g_cpu.instruction_table[0xA7] = anaa;
    g_cpu.instruction_table[0xA8] = xrab;
    g_cpu.instruction_table[0xA9] = xrac;
    g_cpu.instruction_table[0xAA] = xrad;
    g_cpu.instruction_table[0xAB] = xrae;
    g_cpu.instruction_table[0xAC] = xrah;
    g_cpu.instruction_table[0xAD] = xral;
    g_cpu.instruction_table[0xAE] = xram;
    g_cpu.instruction_table[0xAF] = xraa;
    g_cpu.instruction_table[0xB0] = orab;
    g_cpu.instruction_table[0xB1] = orac;
    g_cpu.instruction_table[0xB2] = orad;
    g_cpu.instruction_table[0xB3] = orae;
    g_cpu.instruction_table[0xB4] = orah;
    g_cpu.instruction_table[0xB5] = oral;
    g_cpu.instruction_table[0xB6] = oram;
    g_cpu.instruction_table[0xB7] = oraa;
    g_cpu.instruction_table[0xB8] = cmpb;
    g_cpu.instruction_table[0xB9] = cmpc;
    g_cpu.instruction_table[0xBA] = cmpd;
    g_cpu.instruction_table[0xBB] = cmpe;
    g_cpu.instruction_table[0xBC] = cmph;
    g_cpu.instruction_table[0xBD] = cmpl;
    g_cpu.instruction_table[0xBE] = cmpm;
    g_cpu.instruction_table[0xBF] = cmpa;
    g_cpu.instruction_table[0xC0] = rnz;
    g_cpu.instruction_table[0xC1] = popb;
    g_cpu.instruction_table[0xC2] = jnz;
    g_cpu.instruction_table[0xC3] = jmp;
    g_cpu.instruction_table[0xC4] = cnz;
    g_cpu.instruction_table[0xC5] = pushb;
    g_cpu.instruction_table[0xC6] = adi;
    g_cpu.instruction_table[0xC8] = rz;
    g_cpu.instruction_table[0xC9] = ret;
    g_cpu.instruction_table[0xCA] = jz;
    g_cpu.instruction_table[0xCC] = cz;
    g_cpu.instruction_table[0xCD] = call;
    g_cpu.instruction_table[0xCE] = aci;
    g_cpu.instruction_table[0xD0] = rnc;
    g_cpu.instruction_table[0xD1] = popd;
    g_cpu.instruction_table[0xD2] = jnc;
    g_cpu.instruction_table[0xD3] = out;
    g_cpu.instruction_table[0xD4] = cnc;
    g_cpu.instruction_table[0xD5] = pushd;
    g_cpu.instruction_table[0xD6] = sui;
    g_cpu.instruction_table[0xD8] = rc;
    g_cpu.instruction_table[0xDA] = jc;
    g_cpu.instruction_table[0xDB] = in;
    g_cpu.instruction_table[0xDC] = cc;
    g_cpu.instruction_table[0xDE] = sbi;
    g_cpu.instruction_table[0xE0] = rpo;
    g_cpu.instruction_table[0xE1] = poph;
    g_cpu.instruction_table[0xE2] = jpo;
    g_cpu.instruction_table[0xE3] = xthl;
    g_cpu.instruction_table[0xE4] = cpo;
    g_cpu.instruction_table[0xE5] = pushh;
    g_cpu.instruction_table[0xE6] = ani;
    g_cpu.instruction_table[0xE8] = rpe;
    g_cpu.instruction_table[0xE9] = pchl;
    g_cpu.instruction_table[0xEA] = jpe;
    g_cpu.instruction_table[0xEB] = xchg;
    g_cpu.instruction_table[0xEC] = cpe;
    g_cpu.instruction_table[0xEE] = xri;
    g_cpu.instruction_table[0xF0] = rp;
    g_cpu.instruction_table[0xF1] = poppsw;
    g_cpu.instruction_table[0xF2] = jp;
    g_cpu.instruction_table[0xF3] = di;
    g_cpu.instruction_table[0xF4] = cp;
    g_cpu.instruction_table[0xF5] = pushpsw;
    g_cpu.instruction_table[0xF6] = ori;
    g_cpu.instruction_table[0xF8] = rm;
    g_cpu.instruction_table[0xF9] = sphl;
    g_cpu.instruction_table[0xFA] = jm;
    g_cpu.instruction_table[0xFB] = ei;
    g_cpu.instruction_table[0xFC] = cm;
    g_cpu.instruction_table[0xFE] = cpi;
}