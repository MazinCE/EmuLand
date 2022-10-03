#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SDL_SCREEN_WIDTH 640
#define SDL_SCREEN_HEIGHT 480

#define CHIP8_SCREEN_WIDTH 64
#define CHIP8_SCREEN_HEIGHT 32

typedef struct
{
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Texture *scr;
    uint32_t frameBuffer[CHIP8_SCREEN_WIDTH * CHIP8_SCREEN_HEIGHT];
    bool dirty;
} Display;

void Display_Init(void);
void Display_Destroy(void);
void Display_Clear(void);
void Display_Render(void);
void Display_ClearFrameBuffer(void);
uint32_t Display_GetPixel(uint8_t x, uint8_t y);
void Display_SetPixel(uint8_t x, uint8_t y, uint32_t val);
void Display_SetDirty(void);
