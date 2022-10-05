#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdint.h>

#define SDL_WINDOW_WIDTH 640
#define SDL_WINDOW_HEIGHT 480

#define ARCADE_WINDOW_WIDTH 256
#define ARCADE_WINDOW_HEIGHT 224

typedef struct
{
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Texture *scr;

    uint32_t frameBuffer[ARCADE_WINDOW_WIDTH * ARCADE_WINDOW_HEIGHT];
} Display;

void Display_Init(void);
void Display_Destroy(void);

void Display_Render(void);
void Display_SetPixel(uint8_t x, uint8_t y);

#endif // DISPLAY_H