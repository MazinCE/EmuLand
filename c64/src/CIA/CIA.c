#include "CIA.h"
#include "../c64bus.h"
#include <stdlib.h>

Cia *Cia_Create()
{
    Cia *instance = (Cia *)malloc(sizeof(Cia));

    instance->timer[0] = IntervalTimer_Create(0x01);
    instance->timer[1] = IntervalTimer_Create(0x02);

    return instance;
}

void Cia_Destroy(Cia *self)
{
    free(self->timer[0]);
    free(self->timer[1]);
    free(self);
}

void Cia_Tick(Cia *self)
{
    IntervalTimer_Tick(self->timer[0]);
    IntervalTimer_Tick(self->timer[1]);

    if (Cia_GeneratedInterrupt(self))
    {
        C64Bus_CpuInterrupt(INTERRUPT_IRQ);
    }
}

bool Cia_GeneratedInterrupt(Cia *self)
{
    if (IntervalTimer_TimerUnderflow(self->timer[0]))
    {
        self->interruptControl.data |= self->timer[0]->interruptMask;
    }

    if (IntervalTimer_TimerUnderflow(self->timer[1]))
    {
        self->interruptControl.data |= self->timer[1]->interruptMask;
    }

    if (self->interruptControl.data)
    {
        self->interruptControl.data |= 0x80; // set IR bit
    }

    return self->interruptControl.data & self->interruptControl.mask;
}

uint8_t Cia_Read(Cia *self, uint16_t addr)
{
    switch (addr & 0xFF)
    {
    case PRA:
        return self->port[0].pr;
    case DDRA:
        return self->port[0].ddr;
    case PRB:
        return self->port[1].pr;
    case DDRB:
        return self->port[1].ddr;
    case TALO:
        return IntervalTimer_GetCounterLo(self->timer[0]);
    case TAHI:
        return IntervalTimer_GetCounterHi(self->timer[0]);
    case TBLO:
        return IntervalTimer_GetCounterLo(self->timer[1]);
    case TBHI:
        return IntervalTimer_GetCounterHi(self->timer[1]);
    case ICR:
    {
        uint8_t temp = self->interruptControl.data;
        self->interruptControl.data = 0;
        return temp;
    }
    case CRA:
        return self->timer[0]->control;
    case CRB:
        return self->timer[1]->control;
    }

    return 0;
}

void Cia_Write(Cia *self, uint16_t addr, uint8_t data)
{
    uint8_t selectedReg = addr & 0x0FF;

    switch (selectedReg)
    {
    case PRA:
        self->port[0].pr = data;
        break;
    case DDRA:
        self->port[0].ddr = data;
        break;
    case PRB:
        self->port[1].pr = data;
        break;
    case DDRB:
        self->port[1].ddr = data;
        break;
    case TALO:
        IntervalTimer_SetLatchLo(self->timer[0], data);
        break;
    case TAHI:
        IntervalTimer_SetLatchHi(self->timer[0], data);
        break;
    case TBLO:
        IntervalTimer_SetLatchLo(self->timer[1], data);
        break;
    case TBHI:
        IntervalTimer_SetLatchHi(self->timer[1], data);
        break;
    case ICR:
    {
        uint8_t interruptMask = self->interruptControl.mask;
        self->interruptControl.mask = (data & 0x80) ? (interruptMask | data) : (interruptMask & (~data));
    }
    break;
    case CRA:
        self->timer[0]->control = data;
        break;
    case CRB:
        self->timer[1]->control = data;
        break;
    }
}