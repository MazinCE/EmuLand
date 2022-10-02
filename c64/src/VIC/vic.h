#ifndef VIC_H
#define VIC_H

#include "vic_graphics.h"
#include "vic_border.h"
#include "vic_sprite.h"
#include "vic_defines.h"

#define C64_SCREEN_WIDTH 368
#define C64_SCREEN_HEIGHT 270

typedef struct
{
    VicGraphics graphics;
    VicSprite sprite;
    VicBorder border;
    uint16_t rasterCompare;
    uint8_t cycle;
    bool displayEnabled;
    VicPixel videoFrame[C64_SCREEN_WIDTH * C64_SCREEN_HEIGHT];
    uint8_t registers[REGISTERS_MAX];

} Vic;

extern Vic g_vic;

void Vic_Init(void);
void Vic_Tick(void);

uint8_t Vic_Read(uint16_t addr);
void Vic_Write(uint16_t addr, uint8_t data);

void Vic_PutPixel(uint8_t xOffset, uint16_t y, VicPixel pixel);

bool Vic_GeneratedInterrupt(void);

uint16_t Vic_GetRaster(void);
void Vic_SetRaster(uint16_t val);
bool Vic_IsBadLine(void);

#endif