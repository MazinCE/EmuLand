#include "display.h"

Display g_dis;

void Display_Init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_ERROR: %s\n", SDL_GetError());
    }

    g_dis.win = SDL_CreateWindow("Space Invaders",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOW_WIDTH,
                                 SDL_WINDOW_HEIGHT,
                                 SDL_WINDOW_SHOWN);

    g_dis.ren = SDL_CreateRenderer(g_dis.win, -1, SDL_RENDERER_ACCELERATED);

    g_dis.scr = SDL_CreateTexture(g_dis.ren,
                                  SDL_PIXELFORMAT_RGB888,
                                  SDL_TEXTUREACCESS_STREAMING,
                                  ARCADE_WINDOW_WIDTH,
                                  ARCADE_WINDOW_HEIGHT);

    SDL_RenderSetScale(g_dis.ren, 2, 2);
}

void Display_Destroy(void)
{
    SDL_DestroyTexture(g_dis.scr);
    SDL_DestroyRenderer(g_dis.ren);
    SDL_DestroyWindow(g_dis.win);
    SDL_Quit();
}

void Display_ClearFrameBuffer(void)
{
    memset(g_dis.frameBuffer, 0x00000000, sizeof(g_dis.frameBuffer));
}

void Display_Render(void)
{
    SDL_RenderClear(g_dis.ren);
    SDL_UpdateTexture(g_dis.scr, 0, g_dis.frameBuffer, ARCADE_WINDOW_WIDTH * sizeof(uint32_t));
    SDL_RenderCopyEx(g_dis.ren, g_dis.scr, 0, 0, 0.0, 0, 0);
    SDL_RenderPresent(g_dis.ren);
}

void Display_SetPixel(uint8_t x, uint8_t y)
{
    uint32_t color = 0xFFFFFF;

    g_dis.frameBuffer[x + y * ARCADE_WINDOW_WIDTH] = color;
}