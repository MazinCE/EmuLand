#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct
{
    bool isDown;
    uint32_t code;
} Key;

typedef struct
{
    Key keyMatrix[64];
} Keyboard;

void Keyboard_Init(void);
void Keyboard_RegisterKeyPress(SDL_KeyboardEvent *e);
void Keyboard_Emulate(void);

#endif