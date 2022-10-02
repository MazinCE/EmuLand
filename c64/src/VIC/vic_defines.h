#ifndef VIC_DEFS_H
#define VIC_DEFS_H

#include <stdbool.h>

enum VicRegister
{
    X_COORDINATE_SPRITE_0 = 0x00,
    Y_COORDINATE_SPRITE_0 = 0x01,
    X_COORDINATE_MSB = 0x10,
    CONTROL_REGISTER_1 = 0x11,
    RASTER = 0x12,
    SPRITE_ENABLED = 0x15,
    CONTROL_REGISTER_2 = 0x16,
    SPRITE_Y_EXPANSION = 0x17,
    MEMORY_POINTERS = 0x18,
    INTERRUPT_REGISTER = 0x19,
    INTERRUPT_ENABLED = 0x1A,
    SPRITE_PRIORITY = 0x1B,
    SPRITE_MULTICOLOR = 0x1C,
    SPRITE_X_EXPANSION = 0x1D,
    SPRITE_SPRITE_COLLISION = 0x1E,
    SPRITE_GRAPHICS_COLLISION = 0x1F,
    BORDER_COLOR = 0x20,
    BACKGROUND_COLOR_0 = 0x21,
    BACKGROUND_COLOR_1 = 0x22,
    BACKGROUND_COLOR_2 = 0x23,
    BACKGROUND_COLOR_3 = 0x24,
    SPRITE_MULTICOLOR_0 = 0x25,
    SPRITE_MULTICOLOR_1 = 0x26,
    SPRITE_COLOR_0 = 0x27,
    REGISTERS_MAX = 47,
};

typedef enum
{
    PIXEL_BACKGROUND = 0,
    PIXEL_SPRITE_0,
    PIXEL_SPRITE_1,
    PIXEL_SPRITE_2,
    PIXEL_SPRITE_3,
    PIXEL_SPRITE_4,
    PIXEL_SPRITE_5,
    PIXEL_SPRITE_6,
    PIXEL_SPRITE_7,
    PIXEL_FOREGROUND,
    PIXEL_BORDER,

} VicPixelType;

typedef struct
{
    uint32_t color : 24;
    VicPixelType type : 8;

} VicPixel;

typedef struct
{
    uint8_t leftEnd;
    uint16_t rightStart;
    uint8_t topEnd;
    uint8_t bottomStart;
    bool verticalEnabled;
    bool mainEnabled;

} VicBorder;

typedef struct
{
    uint8_t dataCounter[8];
    uint8_t dataBaseCounter[8];
    uint32_t shiftRegister[8];
    bool expansion[8];
    bool dma[8];
    bool displayEnabled[8];

} VicSprite;

typedef enum
{
    STANDARD_TEXT_MODE = 0,
    MULTICOLOR_TEXT_MODE,
    STANDARD_BITMAP_MODE,
    MULTICOLOR_BITMAP_MODE,
    ECM_TEXT_MODE,

} VicGraphicsMode;

typedef struct
{
    VicGraphicsMode mode;
    uint8_t rowCounter;
    uint16_t videoCounter;
    uint16_t videoBaseCounter;
    bool isIdle;

} VicGraphics;

#endif