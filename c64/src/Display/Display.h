#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../c64_color.h"

#define SDL_WINDOW_WIDTH 736
#define SDL_WINDOW_HEIGHT 540

typedef struct
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* screen;
} Display;

void Display_Init(void);
void Display_Distroy(void);
void Display_Render(void);

#endif