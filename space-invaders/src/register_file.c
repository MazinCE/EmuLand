#include "register_file.h"

RegisterFile g_reg_file;

uint8_t RegisterFile_ReadRegister(WorkRegister reg)
{
    uint8_t *registers = TO_UINT8_ARRAY(g_reg_file);
    return registers[reg];
}

uint16_t RegisterFile_ReadRegisterPair(RegisterPair reg_pair)
{
    uint16_t *register_pairs = TO_UINT16_ARRAY(g_reg_file);

    return register_pairs[reg_pair];
}

void RegisterFile_WriteRegister(WorkRegister reg, uint8_t val)
{
    uint8_t *registers = TO_UINT8_ARRAY(g_reg_file);
    registers[reg] = val;
}

void RegisterFile_WriteRegisterPair8(RegisterPair reg_pair, uint8_t upper, uint8_t lower)
{
    uint8_t *register_pairs = TO_UINT8_ARRAY(g_reg_file);
    register_pairs[reg_pair] = upper;
    register_pairs[reg_pair + 1] = lower;
}

void RegisterFile_WriteRegisterPair16(RegisterPair reg_pair, uint16_t val)
{
    uint16_t *register_pairs = TO_UINT16_ARRAY(g_reg_file);
    register_pairs[reg_pair] = val;
}