#include "memory.h"
#include <stdlib.h>

Memory *Memory_Create(uint8_t bus_width)
{
    Memory *mem = (Memory *)malloc(sizeof(Memory));

    mem->data = (uint8_t *)malloc(bus_width);
    mem->addr_mask = (1 << bus_width) - 1;

    return mem;
}

void Memory_Destroy(Memory *mem)
{
    free(mem->data);
    free(mem);
}

void Memory_LoadFromFile(Memory *mem, uint16_t offset, const char *path)
{
    
}

uint8_t Memory_Read(Memory *mem, uint16_t addr)
{
    return mem->data[addr & mem->addr_mask];
}

void Memory_Write(Memory *mem, uint16_t addr, uint8_t data)
{
    mem->data[addr & mem->addr_mask] = data;
}