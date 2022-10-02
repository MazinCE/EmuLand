#include "vic.h"
#include "../c64bus.h"
#include "../c64_color.h"

void Vic_SpriteGenerate(void)
{
    for (uint8_t i = 0; i < 8; ++i)
    {
        if (g_vic.registers[SPRITE_ENABLED] & (1 << i))
        {
            Vic_SpriteEnableDMA(i);
            Vic_SpriteEnableDisplay(i);
            Vic_SpriteSetExpansion(i);

            if (g_vic.sprite.dma[i])
            {
                Vic_SpriteDMA(i);
            }

            if (g_vic.sprite.displayEnabled[i])
            {
                if (g_vic.cycle >= 12 && g_vic.cycle <= 57)
                {
                    Vic_SpriteDraw(i);
                }
            }
        }
    }
}

void Vic_SpriteSetExpansion(uint8_t spriteNum)
{
    bool sprite_expanded = g_vic.registers[SPRITE_Y_EXPANSION] & (1 << spriteNum);

    if (!sprite_expanded)
    {
        g_vic.sprite.expansion[spriteNum] = 1;
    }

    if (sprite_expanded && g_vic.cycle == 55)
    {
        g_vic.sprite.expansion[spriteNum] = !g_vic.sprite.expansion[spriteNum];
    }

    if (g_vic.sprite.expansion[spriteNum])
    {
        if (g_vic.cycle == 15)
        {
            g_vic.sprite.dataBaseCounter[spriteNum] += 2;
        }
        else if (g_vic.cycle == 16)
        {
            g_vic.sprite.dataBaseCounter[spriteNum]++;
        }
    }

    if (g_vic.cycle == 55 && g_vic.sprite.dataBaseCounter[spriteNum] == 63)
    {
        g_vic.sprite.dma[spriteNum] = 0;
        g_vic.sprite.displayEnabled[spriteNum] = 0;
    }
}

void Vic_SpriteEnableDisplay(uint8_t spriteNum)
{
    if (g_vic.cycle == 58)
    {
        uint16_t raster = Vic_GetRaster() & 0xFF;
        uint8_t spriteY = g_vic.registers[Y_COORDINATE_SPRITE_0 + 2 * spriteNum];

        g_vic.sprite.dataCounter[spriteNum] = g_vic.sprite.dataBaseCounter[spriteNum];

        if (g_vic.sprite.dma[spriteNum] && raster == spriteY)
        {
            g_vic.sprite.displayEnabled[spriteNum] = 1;
        }
    }
}

void Vic_SpriteEnableDMA(uint8_t spriteNum)
{
    if (g_vic.cycle == 55 || g_vic.cycle == 56)
    {
        uint16_t raster = Vic_GetRaster() & 0xFF;
        bool spriteEnabled = g_vic.registers[SPRITE_ENABLED] & (1 << spriteNum);
        uint8_t spriteY = g_vic.registers[Y_COORDINATE_SPRITE_0 + 2 * spriteNum];

        if (spriteEnabled && raster == spriteY)
        {
            g_vic.sprite.dma[spriteNum] = 1;
            g_vic.sprite.dataBaseCounter[spriteNum] = 0;

            if (g_vic.registers[SPRITE_Y_EXPANSION] & (1 << spriteNum))
            {
                g_vic.sprite.expansion[spriteNum] = 0;
            }
        }
    }
}

void Vic_SpriteDMA(uint8_t spriteNum)
{
    switch (g_vic.cycle)
    {
    case 55:
        if (spriteNum == 0)
        {
            C64Bus_SetRDY(0);
        }
        break;
    case 57:
        break;
    case 58:
        if (spriteNum == 0)
        {
            Vic_SpriteReadData(0);
        }
        break;
    case 59:
        if (spriteNum == 0)
        {
            Vic_SpriteReadData(0);
            Vic_SpriteReadData(0);
            C64Bus_Release();
        }
        else if (spriteNum == 2)
        {
        }
        break;
    case 60:
        if (spriteNum == 1)
        {
            Vic_SpriteReadData(1);
        }
        break;
    case 61:
        if (spriteNum == 1)
        {
            Vic_SpriteReadData(1);
            Vic_SpriteReadData(1);
        }
        else if (spriteNum == 3)
        {
        }
        break;
    case 62:
        if (spriteNum == 2)
        {
            Vic_SpriteReadData(2);
        }
        break;
    case 0:
        if (spriteNum == 2)
        {
            Vic_SpriteReadData(2);
            Vic_SpriteReadData(2);
        }
        else if (spriteNum == 4)
        {
        }
        break;
    case 1:
        if (spriteNum == 3)
        {
            Vic_SpriteReadData(3);
        }
        break;
    case 2:
        if (spriteNum == 3)
        {
            Vic_SpriteReadData(3);
            Vic_SpriteReadData(3);
        }
        else if (spriteNum == 5)
        {
        }
        break;
    case 3:
        if (spriteNum == 4)
        {
            Vic_SpriteReadData(4);
        }
        break;
    case 4:
        if (spriteNum == 4)
        {
            Vic_SpriteReadData(4);
            Vic_SpriteReadData(4);
        }
        else if (spriteNum == 6)
        {
        }
        break;
    case 5:
        if (spriteNum == 5)
        {
            Vic_SpriteReadData(5);
        }
        break;
    case 6:
        if (spriteNum == 5)
        {
            Vic_SpriteReadData(5);
            Vic_SpriteReadData(5);
        }
        else if (spriteNum == 7)
        {
        }
        break;
    case 7:
        if (spriteNum == 6)
        {
            Vic_SpriteReadData(6);
        }
        break;
    case 8:
        if (spriteNum == 6)
        {
            Vic_SpriteReadData(6);
            Vic_SpriteReadData(6);
        }
        break;
    case 9:
        if (spriteNum == 7)
        {
            Vic_SpriteReadData(7);
        }
        break;
    case 10:
        if (spriteNum == 7)
        {
            Vic_SpriteReadData(7);
            Vic_SpriteReadData(7);
        }
        break;
    }
}

void Vic_SpriteDraw(uint8_t spriteNum)
{
    uint16_t raster = Vic_GetRaster() - 16;
    uint16_t spriteX = Vic_SpriteGetX(spriteNum);

    uint8_t i = 0;

    while (i < 8)
    {
        uint16_t xCoord = i + (g_vic.cycle - 12) * 8;

        if (g_vic.registers[SPRITE_MULTICOLOR] & (1 << spriteNum))
        {
            if (xCoord >= spriteX)
            {
                uint8_t bit0 = g_vic.sprite.shiftRegister[spriteNum] & 0x800000 ? 1 : 0;
                uint8_t bit1 = g_vic.sprite.shiftRegister[spriteNum] & 0x400000 ? 1 : 0;

                uint8_t color_src = (bit0 << 1) | bit1;

                VicPixel pixel = {
                    .color = C64_COLORS[g_vic.registers[SPRITE_MULTICOLOR_0] & 0x0F],
                    .type = (VicPixelType)(PIXEL_SPRITE_0 + spriteNum),
                };

                switch (color_src)
                {
                case 0x02:
                    pixel.color = C64_COLORS[g_vic.registers[SPRITE_COLOR_0 + spriteNum] & 0x0F];
                    break;
                case 0x03:
                    pixel.color = C64_COLORS[g_vic.registers[SPRITE_MULTICOLOR_1] & 0x0F];
                    break;
                }

                if (color_src)
                {
                    Vic_SpriteCheckCollision(xCoord, raster, spriteNum);

                    if (Vic_SpriteCanDrawPixel(xCoord, raster, spriteNum))
                    {
                        Vic_PutPixel(i, raster, pixel);
                        Vic_PutPixel(i + 1, raster, pixel);
                    }
                }

                if (g_vic.registers[SPRITE_X_EXPANSION] & (1 << spriteNum))
                {
                    if (!(i % 4))
                    {
                        g_vic.sprite.shiftRegister[spriteNum] <<= 2;
                    }
                }
                else
                {
                    g_vic.sprite.shiftRegister[spriteNum] <<= 2;
                }
            }

            i += 2;
        }
        else
        {
            if (xCoord >= spriteX)
            {
                VicPixel pixel = {
                    .color = C64_COLORS[g_vic.registers[SPRITE_COLOR_0 + spriteNum] & 0x0F],
                    .type = (VicPixelType)(PIXEL_SPRITE_0 + spriteNum),
                };

                if (g_vic.sprite.shiftRegister[spriteNum] & 0x800000)
                {
                    Vic_SpriteCheckCollision(xCoord, raster, spriteNum);

                    if (Vic_SpriteCanDrawPixel(xCoord, raster, spriteNum))
                    {
                        Vic_PutPixel(i, raster, pixel);
                    }
                }

                if (g_vic.registers[SPRITE_X_EXPANSION] & (1 << spriteNum))
                {
                    if (i % 2)
                    {
                        g_vic.sprite.shiftRegister[spriteNum] <<= 1;
                    }
                }
                else
                {
                    g_vic.sprite.shiftRegister[spriteNum] <<= 1;
                }
            }
            i++;
        }
    }
}

void Vic_SpriteReadData(uint8_t spriteNum)
{
    uint8_t vm = g_vic.registers[MEMORY_POINTERS] >> 4;
    uint8_t pointer = C64Bus_VicRead((vm << 10) | 0x3F8 | spriteNum);

    uint8_t data = C64Bus_VicRead((pointer << 6) |
                                  g_vic.sprite.dataCounter[spriteNum]);

    g_vic.sprite.shiftRegister[spriteNum] <<= 8;
    g_vic.sprite.shiftRegister[spriteNum] |= data;
    g_vic.sprite.dataCounter[spriteNum]++;
}

void Vic_SpriteCheckCollision(uint16_t x, uint16_t y, uint8_t spriteNum)
{
    VicPixel backgroundPixel = g_vic.videoFrame[x + y * 368];

    if (backgroundPixel.type <= PIXEL_SPRITE_7)
    {
        g_vic.registers[SPRITE_SPRITE_COLLISION] |= (1 << spriteNum);
        g_vic.registers[INTERRUPT_REGISTER] |= 0x02;
    }
    else if (backgroundPixel.type == PIXEL_FOREGROUND)
    {
        g_vic.registers[SPRITE_GRAPHICS_COLLISION] |= (1 << spriteNum);
        g_vic.registers[INTERRUPT_REGISTER] |= 0x04;
    }
}

bool Vic_SpriteCanDrawPixel(uint16_t x, uint16_t y, uint8_t spriteNum)
{
    bool spriteBehindForeground = g_vic.registers[SPRITE_PRIORITY] & (1 << spriteNum);

    VicPixel backgroundPixel = g_vic.videoFrame[x + y * 368];
    VicPixelType pixelType = (VicPixelType)(PIXEL_SPRITE_0 + spriteNum);

    if (backgroundPixel.type != PIXEL_BORDER)
    {
        if (backgroundPixel.type == PIXEL_BACKGROUND)
        {
            return 1;
        }

        if (backgroundPixel.type <= PIXEL_SPRITE_7)
        {
            return pixelType <= backgroundPixel.type;
        }

        if (!spriteBehindForeground)
        {
            return 1;
        }
    }

    return 0;
}

uint16_t Vic_SpriteGetX(uint8_t spriteNum)
{
    uint16_t xCoordMSB = g_vic.registers[X_COORDINATE_MSB] & (1 << spriteNum) ? 0x100 : 0;
    uint8_t xCoord = g_vic.registers[X_COORDINATE_SPRITE_0 + 2 * spriteNum];

    return xCoordMSB | xCoord;
}