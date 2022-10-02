#ifndef VIC_SPRITE_H
#define VIC_SPRITE_H

#include <stdint.h>
#include <stdbool.h>

void Vic_SpriteGenerate(void);

void Vic_SpriteSetExpansion(uint8_t spriteNum);
void Vic_SpriteEnableDisplay(uint8_t spriteNum);

void Vic_SpriteEnableDMA(uint8_t spriteNum);
void Vic_SpriteDMA(uint8_t spriteNum);

void Vic_SpriteDraw(uint8_t spriteNum);
void Vic_SpriteReadData(uint8_t spriteNum);

void Vic_SpriteCheckCollision(uint16_t x, uint16_t y, uint8_t spriteNum);
bool Vic_SpriteCanDrawPixel(uint16_t x, uint16_t y, uint8_t spriteNum);

uint16_t Vic_SpriteGetX(uint8_t spriteNum);

#endif