#include "vic.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "../c64_color.h"
#include "../c64bus.h"
#include <assert.h>

Vic g_vic;

void Vic_Init()
{
    g_vic.cycle = 0;

    memset(g_vic.registers, 0, 47);
    memset(g_vic.videoFrame, 0, 368 * 270 * sizeof(uint32_t));
}

void Vic_Tick()
{
    uint16_t raster = Vic_GetRaster();

    if (raster >= 16 && raster <= 285)
    {
        Vic_GraphicsGenerate();
        Vic_SpriteGenerate();
        Vic_BorderGenerate();
    }

    if (raster == 48)
    {
        g_vic.displayEnabled = g_vic.registers[CONTROL_REGISTER_1] & 0x10;
    }

    if (g_vic.cycle == 0)
    {
        Vic_SetRaster(raster + 1);

        if (Vic_GetRaster() == g_vic.rasterCompare)
        {
            g_vic.registers[INTERRUPT_REGISTER] |= 0x01;
        }

        if (Vic_GeneratedInterrupt())
        {
            C64Bus_CpuInterrupt(INTERRUPT_IRQ);
        }
    }

    g_vic.cycle = (g_vic.cycle + 1) % 63;
}

uint8_t Vic_Read(uint16_t addr)
{
    uint8_t regSelect = addr & 0xFF;

    if (regSelect == SPRITE_SPRITE_COLLISION ||
        regSelect == SPRITE_GRAPHICS_COLLISION)
    {
        uint8_t temp = g_vic.registers[regSelect];
        g_vic.registers[regSelect] = 0;
        return temp;
    }

    return g_vic.registers[regSelect];
}

void Vic_Write(uint16_t addr, uint8_t data)
{
    switch (addr & 0xFF)
    {
    case RASTER:
        g_vic.rasterCompare = (g_vic.rasterCompare & 0x100) | data;
        break;
    case CONTROL_REGISTER_1:
        g_vic.registers[CONTROL_REGISTER_1] = data;
        g_vic.rasterCompare = (g_vic.rasterCompare & 0xFF) | ((data & 0x80) << 1);
        Vic_BorderSetVertical();
        Vic_GraphicsSetMode();
        break;
    case CONTROL_REGISTER_2:
        g_vic.registers[CONTROL_REGISTER_2] = data;
        Vic_BorderSetMain();
        Vic_GraphicsSetMode();
        break;
    case INTERRUPT_REGISTER:
        g_vic.registers[INTERRUPT_REGISTER] &= ~0x80;
        g_vic.registers[INTERRUPT_REGISTER] = data;
        g_vic.registers[INTERRUPT_REGISTER] |= 0x78;
        break;
    case INTERRUPT_ENABLED:
        g_vic.registers[INTERRUPT_ENABLED] = data;
        break;
    case BORDER_COLOR:
        g_vic.registers[BORDER_COLOR] = data;
        break;
    default:
        g_vic.registers[addr & 0xFF] = data;
        break;
    };
}

void Vic_PutPixel(uint8_t xOffset, uint16_t y, VicPixel pixel)
{
    g_vic.videoFrame[(xOffset + (g_vic.cycle - 12) * 8) + y * 368] = pixel;
}

bool Vic_GeneratedInterrupt()
{
    bool generated = g_vic.registers[INTERRUPT_REGISTER] & g_vic.registers[INTERRUPT_ENABLED];

    if (generated)
    {
        g_vic.registers[INTERRUPT_REGISTER] |= 0x80;
    }

    return generated;
}

uint16_t Vic_GetRaster()
{
    uint16_t msb = g_vic.registers[CONTROL_REGISTER_1] & 0x80 ? 0x100 : 0;

    return (msb | g_vic.registers[RASTER]) % 312;
}

void Vic_SetRaster(uint16_t val)
{
    uint8_t rasterMSB = (val & 0x100) >> 1;
    uint8_t controlRegister1 = g_vic.registers[CONTROL_REGISTER_1];

    g_vic.registers[CONTROL_REGISTER_1] = (controlRegister1 & 0x7F) | rasterMSB;
    g_vic.registers[RASTER] = val & 0xFF;
}

bool Vic_IsBadLine()
{
    if (!g_vic.displayEnabled)
    {
        return 0;
    }

    uint16_t raster = Vic_GetRaster();

    if (raster < 48 || raster > 247)
    {
        return 0;
    }

    uint8_t yScroll = g_vic.registers[CONTROL_REGISTER_1] & 0x07;

    if (yScroll != (raster & 0x07))
    {
        return 0;
    }

    return 1;
}
