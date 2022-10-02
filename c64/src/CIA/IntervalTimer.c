#include "IntervalTimer.h"
#include <stdlib.h>

IntervalTimer *IntervalTimer_Create(uint8_t interruptMask)
{
    IntervalTimer *instance = (IntervalTimer *)malloc(sizeof(IntervalTimer));
    instance->counter = 0;
    instance->interruptMask = interruptMask;

    return instance;
}

void IntervalTimer_Tick(IntervalTimer *self)
{
    // force load?
    if (self->control & 0x10)
    {
       self->counter = self->latch;
       self->control &= 0xEF;
    }

    // timer running?
    if (!(self->control & 0x01))
    {
        return;
    }

    // timer underflow?
    if ((self->counter--) == 0)
    {
        self->counter = self->latch;

        // timer mode one-shot?
        if (self->control & 0x08)
        {
            self->control &= 0xFE;
        }

        self->underflow = true;
    }
}

void IntervalTimer_SetLatchLo(IntervalTimer *self, uint8_t val)
{
    self->latch = (self->latch & 0xFF00) | val;
}

void IntervalTimer_SetLatchHi(IntervalTimer *self, uint8_t val)
{
    self->latch = (self->latch & 0x00FF) | (val << 8);
}

uint8_t IntervalTimer_GetCounterHi(IntervalTimer *self)
{
    return self->counter & 0xFF;
}

uint8_t IntervalTimer_GetCounterLo(IntervalTimer *self)
{
    return self->counter >> 8;
}

bool IntervalTimer_TimerUnderflow(IntervalTimer *self)
{
    bool underflowTemp = self->underflow;
    self->underflow = false;
    return underflowTemp;
}
