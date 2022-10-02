#include "vic.h"
#include "../c64_color.h"
#include "../c64bus.h"

void Vic_GraphicsGenerate(void)
{
    uint16_t raster = Vic_GetRaster();

    if (raster == 48 && g_vic.cycle == 0)
    {
        g_vic.graphics.videoBaseCounter = 0;
    }

    if (g_vic.cycle == 14)
    {
        g_vic.graphics.videoCounter = g_vic.graphics.videoBaseCounter;

        if (Vic_IsBadLine())
        {
            g_vic.graphics.rowCounter = 0;
        }
    }

    if (g_vic.graphics.isIdle)
    {
        Vic_GraphicsIdle();
    }
    else
    {
        Vic_GraphicsDisplay();
    }
}

void Vic_GraphicsDisplay(void)
{
    if (g_vic.cycle == 12)
    {
        if (Vic_IsBadLine())
        {
            C64Bus_SetRDY(0);
        }
        else
        {
            C64Bus_Release();
        }
    }
    else if (g_vic.cycle >= 15 && g_vic.cycle <= 54)
    {
        Vic_GraphicsDraw();
    }
    else if (g_vic.cycle == 58)
    {
        if (g_vic.graphics.rowCounter == 7)
        {
            g_vic.graphics.videoBaseCounter = g_vic.graphics.videoCounter;
            g_vic.graphics.isIdle = 1;
            C64Bus_Release();
        }
        else
        {
            g_vic.graphics.rowCounter++;
        }
    }
}

void Vic_GraphicsIdle(void)
{
    if (g_vic.cycle >= 12 && g_vic.cycle <= 57)
    {
        Vic_GraphicsIdleDraw();
    }

    if (Vic_IsBadLine())
    {
        g_vic.graphics.isIdle = 0;
    }
}

void Vic_GraphicsDraw(void)
{
    uint16_t raster = Vic_GetRaster() - 16;
    uint8_t i = 0;
    // uint8_t xScroll = g_vic.registers[CONTROL_REGISTER_2] & 0x07;

    while (i < 8)
    {
        switch (g_vic.graphics.mode)
        {
        case STANDARD_TEXT_MODE:
        {
            uint16_t rowData = Vic_GraphicsReadCharacterGenerator();

            VicPixel pixel = {
                .color = C64_COLORS[g_vic.registers[BACKGROUND_COLOR_0] & 0x0F],
                .type = PIXEL_BACKGROUND,
            };

            if (rowData & (0x80 >> i))
            {
                pixel.color = C64_COLORS[rowData >> 8];
                pixel.type = PIXEL_FOREGROUND;
            }

            Vic_PutPixel(i++, raster, pixel);
        }
        break;
        case MULTICOLOR_TEXT_MODE:
        {
            uint16_t rowData = Vic_GraphicsReadCharacterGenerator();
            uint16_t mc = rowData & 0x800;

            if (!mc)
            {
                VicPixel pixel = {
                    .color = C64_COLORS[g_vic.registers[BACKGROUND_COLOR_0] & 0x0F],
                    .type = PIXEL_BACKGROUND,
                };

                if (rowData & (0x80 >> i))
                {
                    pixel.color = C64_COLORS[(rowData >> 8) & 0x07];
                }

                Vic_PutPixel(i++, raster, pixel);
            }
            else
            {
                uint8_t bit0 = rowData & (0x80 >> i) ? 1 : 0;
                uint8_t bit1 = rowData & (0x40 >> i) ? 1 : 0;

                uint8_t color_src = (bit0 << 1) | bit1;

                VicPixel pixel = {
                    .color = C64_COLORS[g_vic.registers[BACKGROUND_COLOR_0 + color_src] & 0x0F],
                    .type = PIXEL_BACKGROUND,
                };

                if (color_src == 0x02)
                {
                    pixel.type = PIXEL_FOREGROUND;
                }
                else if (color_src == 0x03)
                {
                    pixel.color = C64_COLORS[(rowData >> 8) & 0x07];
                    pixel.type = PIXEL_FOREGROUND;
                }

                Vic_PutPixel(i++, raster, pixel);
                Vic_PutPixel(i++, raster, pixel);
            }
        }
        break;
        case STANDARD_BITMAP_MODE:
        {
            uint16_t rowData = Vic_GraphicsReadBitmap();

            VicPixel pixel = {
                .color = C64_COLORS[rowData >> 12],
                .type = PIXEL_BACKGROUND,
            };

            if (rowData & (0x80 >> i))
            {
                pixel.color = C64_COLORS[(rowData >> 8) & 0x0F];
                pixel.type = PIXEL_FOREGROUND;
            }

            Vic_PutPixel(i++, raster, pixel);
        }
        break;
        case MULTICOLOR_BITMAP_MODE:
        {
            uint16_t colors = Vic_GraphicsReadVideoMatrix();
            uint8_t pixels = Vic_GraphicsReadBitmap();

            uint8_t bit0 = pixels & (0x80 >> i) ? 1 : 0;
            uint8_t bit1 = pixels & (0x40 >> i) ? 1 : 0;

            uint8_t color_src = (bit0 << 1) | bit1;

            VicPixel pixel = {
                .color = C64_COLORS[g_vic.registers[BACKGROUND_COLOR_0] & 0x0F],
                .type = PIXEL_BACKGROUND,
            };

            switch (color_src)
            {
            case 0x01:
                pixel.color = C64_COLORS[(colors >> 4) & 0x0F];
                break;
            case 0x02:
                pixel.color = C64_COLORS[colors & 0x0F];
                pixel.type = PIXEL_FOREGROUND;
                break;
            case 0x03:
                pixel.color = C64_COLORS[colors >> 8];
                pixel.type = PIXEL_FOREGROUND;
                break;
            }

            Vic_PutPixel(i++, raster, pixel);
            Vic_PutPixel(i++, raster, pixel);
        }
        break;
        case ECM_TEXT_MODE:
        {
            uint16_t rowData = Vic_GraphicsReadCharacterGenerator();
            uint8_t backgroundIndex = (rowData >> 12) & 0x03;
            
            VicPixel pixel = {
                .color = C64_COLORS[g_vic.registers[BACKGROUND_COLOR_0 + backgroundIndex] & 0x0F],
                .type = PIXEL_BACKGROUND,
            };

            if (rowData & (0x80 >> i))
            {
                pixel.color = C64_COLORS[(rowData >> 8) & 0x0F];
                pixel.type = PIXEL_FOREGROUND;
            }

            Vic_PutPixel(i++, raster, pixel);
        }
        break;
        }
    }

    g_vic.graphics.videoCounter++;
}

void Vic_GraphicsIdleDraw(void)
{
    // uint8_t xScroll = g_vic.registers[CONTROL_REGISTER_2] & 0x07;
    uint16_t raster = Vic_GetRaster() - 16;
    uint8_t ecm = g_vic.registers[CONTROL_REGISTER_1] & 0x40;

    uint16_t addr = ecm ? 0x39FF : 0x3FFF;
    uint8_t pixels = C64Bus_VicRead(addr);

    uint8_t i = 0;

    while (i < 8)
    {
        switch (g_vic.graphics.mode)
        {
        case STANDARD_TEXT_MODE:
        case MULTICOLOR_TEXT_MODE:
        case STANDARD_BITMAP_MODE:
        case ECM_TEXT_MODE:
        {
            VicPixel pixel = {
                .color = C64_COLORS[g_vic.graphics.mode == STANDARD_BITMAP_MODE ? 0 : g_vic.registers[BACKGROUND_COLOR_0]],
                .type = PIXEL_BACKGROUND,
            };

            if (pixels & (0x80 >> i))
            {
                pixel.color = C64_COLORS[0];
                pixel.type = PIXEL_FOREGROUND;
            }

            Vic_PutPixel(i++, raster, pixel);
        }
        break;
        case MULTICOLOR_BITMAP_MODE:
        {
            uint8_t bit0 = pixels & (0x80 >> i) ? 1 : 0;
            uint8_t bit1 = pixels & (0x40 >> i) ? 1 : 0;

            uint8_t color_src = (bit0 << 1) | bit1;

            VicPixel pixel = {
                .color = C64_COLORS[g_vic.registers[BACKGROUND_COLOR_0]],
                .type = PIXEL_BACKGROUND,
            };

            if (color_src == 0x01)
            {
                pixel.color = C64_COLORS[0];
            }
            else if (color_src > 0x01)
            {
                pixel.color = C64_COLORS[0];
                pixel.type = PIXEL_FOREGROUND;
            }

            Vic_PutPixel(i++, raster, pixel);
            Vic_PutPixel(i++, raster, pixel);
        }
        break;
        }
    }
}

void Vic_GraphicsSetMode(void)
{
    uint8_t ECMBMM = (g_vic.registers[CONTROL_REGISTER_1] >> 5) & 0x03;
    uint8_t MCM = (g_vic.registers[CONTROL_REGISTER_2] >> 4) & 0x01;

    g_vic.graphics.mode = (VicGraphicsMode)((ECMBMM << 1) | MCM);
}

uint16_t Vic_GraphicsReadVideoMatrix()
{
    uint8_t vm = g_vic.registers[MEMORY_POINTERS] >> 4;
    return C64Bus_VicRead((vm << 10) | g_vic.graphics.videoCounter);
}

uint16_t Vic_GraphicsReadCharacterGenerator(void)
{
    uint16_t videoMatrixData = Vic_GraphicsReadVideoMatrix();
    uint8_t charIndex = g_vic.graphics.mode == ECM_TEXT_MODE ? videoMatrixData & 0x3F : videoMatrixData & 0xFF;

    uint8_t cb = (g_vic.registers[MEMORY_POINTERS] >> 1) & 0x07;

    uint16_t charRowAddress = (cb << 11) |
                              (charIndex << 3) |
                              g_vic.graphics.rowCounter;

    uint8_t charRowPixels = C64Bus_VicRead(charRowAddress);

    if (g_vic.graphics.mode == ECM_TEXT_MODE)
    {
        uint8_t backgroundIndex = (videoMatrixData & 0xFF) >> 6;
        videoMatrixData |= backgroundIndex << 12;
    }
    
    return (videoMatrixData & 0x3F00) | charRowPixels;
}

uint16_t Vic_GraphicsReadBitmap(void)
{
    uint8_t cb = (g_vic.registers[MEMORY_POINTERS] >> 3) & 0x01;

    uint16_t pixelsAddress = (cb << 13) |
                             (g_vic.graphics.videoCounter << 3) |
                             g_vic.graphics.rowCounter;

    uint8_t colors = Vic_GraphicsReadVideoMatrix();
    uint8_t pixels = C64Bus_VicRead(pixelsAddress);

    return (colors << 8) | pixels;
}
