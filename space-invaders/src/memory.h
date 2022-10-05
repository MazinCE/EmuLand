#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

typedef struct
{
    uint32_t addr_mask;
    uint8_t *data;
} Memory;

Memory *Memory_Create(uint8_t bus_width);
void Memory_Destroy(Memory *mem);
void Memory_LoadFromFile(Memory *mem, uint16_t offset, const char *path);

uint8_t Memory_Read(Memory *mem, uint16_t addr);
void Memory_Write(Memory *mem, uint16_t addr, uint8_t data);

#endif // MEMORY_H