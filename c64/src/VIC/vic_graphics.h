#ifndef VIC_GRAPHICS_H
#define VIC_GRAPHICS_H

#include <stdint.h>

void Vic_GraphicsGenerate(void);

void Vic_GraphicsDisplay(void);
void Vic_GraphicsIdle(void);

void Vic_GraphicsDraw(void);
void Vic_GraphicsIdleDraw(void);
void Vic_GraphicsSetMode(void);

uint16_t Vic_GraphicsReadVideoMatrix(void);
uint16_t Vic_GraphicsReadCharacterGenerator(void);
uint16_t Vic_GraphicsReadBitmap(void);

#endif