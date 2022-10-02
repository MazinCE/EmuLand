#ifndef Cia_H
#define Cia_H

#include "IntervalTimer.h"

typedef struct
{
    uint8_t pr;
    uint8_t ddr;

} Port;

typedef struct
{
    uint8_t data;
    uint8_t mask;

} InterruptControl;

typedef struct
{
    IntervalTimer *timer[2];
    Port port[2];
    InterruptControl interruptControl;

} Cia;

Cia *Cia_Create();
void Cia_Destroy(Cia *self);

void Cia_Tick(Cia *self);
bool Cia_GeneratedInterrupt(Cia* self);

uint8_t Cia_Read(Cia *self, uint16_t addr);
void Cia_Write(Cia *self, uint16_t addr, uint8_t data);

enum CiaRegister
{
    PRA = 0,
    PRB,
    DDRA,
    DDRB,
    TALO,
    TAHI,
    TBLO,
    TBHI,
    TOD_10THS,
    TOD_SEC,
    TOD_MIN,
    TOD_HR,
    SDR,
    ICR,
    CRA,
    CRB,
};

#endif