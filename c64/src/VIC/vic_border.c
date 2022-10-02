#include "vic.h"
#include "../c64_color.h"

void Vic_BorderSetMain(void)
{
    uint8_t csel = g_vic.registers[CONTROL_REGISTER_2] & 0x08;

    g_vic.border.leftEnd = csel ? 24 : 31;
    g_vic.border.rightStart = csel ? 344 : 335;
}

void Vic_BorderSetVertical(void)
{
    uint8_t rsel = g_vic.registers[CONTROL_REGISTER_1] & 0x08;

    g_vic.border.topEnd = rsel ? 51 : 55;
    g_vic.border.bottomStart = rsel ? 251 : 247;
}

void Vic_BorderGenerate(void)
{
    uint16_t raster = Vic_GetRaster();

    if (g_vic.cycle < 12 || g_vic.cycle > 57)
    {
        return;
    }

    VicPixel pixel = {
        .color = C64_COLORS[g_vic.registers[BORDER_COLOR] & 0x0F],
        .type = PIXEL_BORDER,
    };

    for (uint8_t i = 0; i < 8; ++i)
    {
        uint16_t x_coord = i + (g_vic.cycle - 12) * 8;

        if (raster == g_vic.border.bottomStart)
        {
            g_vic.border.verticalEnabled = 1;
        }
        else if (raster == g_vic.border.topEnd && g_vic.displayEnabled)
        {
            g_vic.border.verticalEnabled = 0;
        }

        if (x_coord == g_vic.border.rightStart)
        {
            g_vic.border.mainEnabled = 1;
        }
        else if (x_coord == g_vic.border.leftEnd)
        {
            if (!g_vic.border.verticalEnabled)
            {
                g_vic.border.mainEnabled = 0;
            }
        }

        if ( g_vic.border.mainEnabled ||  g_vic.border.verticalEnabled)
        {
            g_vic.videoFrame[x_coord + (raster - 16) * 368] = pixel;
        }
    }
}
