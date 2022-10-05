#include "memory.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

Memory *Memory_Create(uint8_t bus_width)
{
    Memory *mem = (Memory *)malloc(sizeof(Memory));
    uint32_t memSize = 1 << bus_width;
    mem->data = (uint8_t *)malloc(memSize);
    mem->addr_mask = memSize - 1;

    return mem;
}

void Memory_Destroy(Memory *mem)
{
    free(mem->data);
    free(mem);
}

void Memory_LoadFromFile(Memory *mem, uint16_t offset, const char *path)
{
    if (access(path, F_OK) == -1)
    {
        printf("Unable to load rom...\n");
    }
    else
    {
        FILE *rom = fopen(path, "rb");
        fseek(rom, 0, SEEK_END);
        size_t romSize = ftell(rom);
        rewind(rom);
        fread(mem->data + offset, romSize, 1, rom);
        fclose(rom);
    }
}

uint8_t Memory_Read(Memory *mem, uint16_t addr)
{
    return mem->data[addr & mem->addr_mask];
}

void Memory_Write(Memory *mem, uint16_t addr, uint8_t data)
{
    mem->data[addr & mem->addr_mask] = data;
}