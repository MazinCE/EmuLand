#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <stdint.h>

#define TO_UINT16_ARRAY(rf) (uint16_t *)(&rf);
#define TO_UINT8_ARRAY(rf) (uint8_t *)(&rf);

typedef enum
{
    WR_B,
    WR_C,
    WR_D,
    WR_E,
    WR_H,
    WR_L,
    WR_F,
    WR_A,
} WorkRegister;

typedef enum
{
    RP_BC,
    RP_DE,
    RP_HL,
    RP_PSW,
} RegisterPair;

typedef struct
{
    uint16_t BC;
    uint16_t DE;
    uint16_t HL;
    uint16_t PSW;
} RegisterFile;

uint8_t RegFile_ReadReg(WorkRegister reg);
uint16_t RegFile_ReadRegPair(RegisterPair regPair);

void RegFile_WriteReg(WorkRegister reg, uint8_t val);
void RegFile_WriteRegPair8(RegisterPair regPair, uint8_t upper, uint8_t lower);
void RegFile_WriteRegPair16(RegisterPair regPair, uint16_t val);

#endif // REGISTER_FILE_H