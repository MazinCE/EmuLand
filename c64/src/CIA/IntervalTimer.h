#ifndef INTERVAL_TIMER_H
#define INTERVAL_TIMER_H

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint16_t counter;
    uint16_t latch;
    uint8_t control;
    uint8_t interruptMask;
    bool underflow;

} IntervalTimer;

IntervalTimer *IntervalTimer_Create(uint8_t interruptMask);

void IntervalTimer_Tick(IntervalTimer *self);

void IntervalTimer_SetLatchLo(IntervalTimer *self, uint8_t val);
void IntervalTimer_SetLatchHi(IntervalTimer *self, uint8_t val);

uint8_t IntervalTimer_GetCounterHi(IntervalTimer *self);
uint8_t IntervalTimer_GetCounterLo(IntervalTimer *self);

bool IntervalTimer_TimerUnderflow(IntervalTimer *self);

#endif