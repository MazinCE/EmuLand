#ifndef ARCADE_H
#define ARCADE_H

#include <SDL2/SDL.h>

#define ARCADE_TICKS_PERFRAME 33333
#define ARCADE_MS_PERFRAME 16.67f

void Arcade_Init(void);
void Arcade_Destroy(void);
void Arcade_ReadInput(SDL_Event e);
void Arcade_Run(void);
void Arcade_Draw(void);

#endif