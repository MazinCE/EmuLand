#include "Display.h"
#include <stdlib.h>
#include "../c64bus.h"

Display g_Display;

void Display_Init(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    g_Display.window = SDL_CreateWindow("C64",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOW_WIDTH,
                                        SDL_WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN);

    g_Display.renderer = SDL_CreateRenderer(g_Display.window, -1, SDL_RENDERER_ACCELERATED);

    g_Display.screen = SDL_CreateTexture(g_Display.renderer,
                                         SDL_PIXELFORMAT_RGB888,
                                         SDL_TEXTUREACCESS_STREAMING,
                                         C64_SCREEN_WIDTH,
                                         C64_SCREEN_HEIGHT);

    SDL_RenderSetScale(g_Display.renderer, 2, 2);
}

void Display_Distroy(void)
{
    SDL_DestroyTexture(g_Display.screen);
    SDL_DestroyRenderer(g_Display.renderer);
    SDL_DestroyWindow(g_Display.window);
    SDL_Quit();
}

void Display_Render(void)
{
    SDL_UpdateTexture(g_Display.screen, 0, C64Bus_GetVicVideoFrame(), C64_SCREEN_WIDTH * sizeof(uint32_t));
    SDL_RenderCopy(g_Display.renderer, g_Display.screen, 0, 0);
    SDL_RenderPresent(g_Display.renderer);
}
