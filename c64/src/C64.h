#ifndef C64_H
#define C64_H

#include "Keyboard/Keyboard.h"
#include "Display/Display.h"
#include "joystick/joystick.h"

#define PAL_CYCLES_PER_FRAME 19656

void C64_Init(void);
void C64_Destroy(void);

void C64_Run(void);
void C64_HandleWindowEvents(void);

void C64_LoadPRG(const char *path, uint16_t offset);

#endif
