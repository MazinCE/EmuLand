#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

typedef struct
{
    uint8_t *data;
    uint8_t busWidth;
} Memory;

Memory *Memory_Create(uint8_t busWidth);
void Memory_Destroy(Memory *self);

uint8_t Memory_Read(Memory *self, uint16_t addr);
void Memory_Write(Memory *self, uint16_t addr, uint8_t data);

uint32_t Memory_GetSize(Memory *self);

void Memory_LoadROM(Memory *self, const char *path);
void Memory_LoadPRG(Memory *self, uint16_t offset, const char *path);

#endif