#include "display.h"

Display g_dis;

void Display_Init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL_ERROR: %s\n", SDL_GetError());
        return;
    }

    g_dis.win = SDL_CreateWindow("Chip-8",
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_WINDOWPOS_CENTERED,
                                 SDL_SCREEN_WIDTH,
                                 SDL_SCREEN_HEIGHT,
                                 SDL_WINDOW_SHOWN);

    g_dis.ren = SDL_CreateRenderer(g_dis.win, -1, SDL_RENDERER_ACCELERATED);

    g_dis.scr = SDL_CreateTexture(g_dis.ren,
                                  SDL_PIXELFORMAT_RGB888,
                                  SDL_TEXTUREACCESS_STREAMING,
                                  CHIP8_SCREEN_WIDTH,
                                  CHIP8_SCREEN_HEIGHT);

    SDL_RenderSetScale(g_dis.ren,
                       SDL_SCREEN_WIDTH / CHIP8_SCREEN_WIDTH,
                       SDL_SCREEN_HEIGHT / CHIP8_SCREEN_HEIGHT);

    g_dis.dirty = false;
}

void Display_Destroy(void)
{
    SDL_DestroyTexture(g_dis.scr);
    SDL_DestroyRenderer(g_dis.ren);
    SDL_DestroyWindow(g_dis.win);
    SDL_Quit();
}

void Display_Clear(void)
{
    if (g_dis.dirty)
    {
        SDL_RenderClear(g_dis.ren);
    }
}

void Display_Render(void)
{
    if (g_dis.dirty)
    {
        SDL_UpdateTexture(g_dis.scr, 0, g_dis.frameBuffer, CHIP8_SCREEN_WIDTH * sizeof(uint32_t));
        SDL_RenderCopy(g_dis.ren, g_dis.scr, 0, 0);
        SDL_RenderPresent(g_dis.ren);

        g_dis.dirty = false;
    }
}

void Display_ClearFrameBuffer(void)
{
    memset(g_dis.frameBuffer, 0, sizeof(g_dis.frameBuffer));
}

uint32_t Display_GetPixel(uint8_t x, uint8_t y)
{
    return g_dis.frameBuffer[x + y * CHIP8_SCREEN_WIDTH];
}

void Display_SetPixel(uint8_t x, uint8_t y, uint32_t val)
{
    g_dis.frameBuffer[x + y * CHIP8_SCREEN_WIDTH] = val;
}

void Display_SetDirty(void)
{
    g_dis.dirty = true;
}
