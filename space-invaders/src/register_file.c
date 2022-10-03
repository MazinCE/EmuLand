#include "register_file.h"

RegisterFile g_regFile;

uint8_t RegFile_ReadReg(WorkRegister reg)
{
    uint8_t *registers = TO_UINT8_ARRAY(g_regFile);
    return registers[reg];
}

uint16_t RegFile_ReadRegPair(RegisterPair regPair)
{
    uint16_t *register_pairs = TO_UINT16_ARRAY(g_regFile);

    return register_pairs[regPair];
}

void RegFile_WriteReg(WorkRegister reg, uint8_t val)
{
    uint8_t *registers = TO_UINT8_ARRAY(g_regFile);
    registers[reg] = val;
}

void RegFile_WriteRegPair8(RegisterPair regPair, uint8_t upper, uint8_t lower)
{
    uint8_t *registerPairs = TO_UINT8_ARRAY(g_regFile);
    registerPairs[regPair] = upper;
    registerPairs[regPair + 1] = lower;
}

void RegFile_WriteRegPair16(RegisterPair regPair, uint16_t val)
{
    uint16_t *registerPairs = TO_UINT16_ARRAY(g_regFile);
    registerPairs[regPair] = val;
}