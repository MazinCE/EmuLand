#ifndef ADDR_MODES_H
#define ADDR_MODES_H

#include <stdint.h>

uint16_t CPU_AddrMode_ACC();
uint16_t CPU_AddrMode_ABS();
uint16_t CPU_AddrMode_ABSX();
uint16_t CPU_AddrMode_ABSY();
uint16_t CPU_AddrMode_IMM();
uint16_t CPU_AddrMode_IMPL();
uint16_t CPU_AddrMode_IND();
uint16_t CPU_AddrMode_XIND();
uint16_t CPU_AddrMode_INDY();
uint16_t CPU_AddrMode_REL();
uint16_t CPU_AddrMode_ZPG();
uint16_t CPU_AddrMode_ZPGX();
uint16_t CPU_AddrMode_ZPGY();

#endif