#include "Memory.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

Memory *Memory_Create(uint8_t busWidth)
{
    Memory *instance = (Memory *)malloc(sizeof(Memory));
    instance->busWidth = busWidth;
    uint32_t size = Memory_GetSize(instance);

    instance->data = (uint8_t *)malloc(size);

    return instance;
}

void Memory_Destroy(Memory *self)
{
    free(self->data);
    free(self);
}

uint8_t Memory_Read(Memory *self, uint16_t addr)
{
    uint16_t addressMask = Memory_GetSize(self) - 1;
    return self->data[addr & addressMask];
}

void Memory_Write(Memory *self, uint16_t addr, uint8_t data)
{
    uint16_t addressMask = Memory_GetSize(self) - 1;
    self->data[addr & addressMask] = data;
}

uint32_t Memory_GetSize(Memory *self)
{
    return 1 << self->busWidth;
}

void Memory_LoadROM(Memory *self, const char *path)
{
    uint32_t memory_size = Memory_GetSize(self);

    if (access(path, F_OK) == -1)
    {
        for (uint32_t i = 0; i < memory_size; ++i)
        {
            self->data[i] = 0xFF;
        }
    }
    else
    {

        FILE *content = fopen(path, "rb");
        fread(self->data, memory_size, 1, content);
        fclose(content);
    }
}

void Memory_LoadPRG(Memory *self, uint16_t offset, const char *path)
{
    FILE *content = fopen(path, "rb");
    fseek(content, 0, SEEK_END);
    size_t size = ftell(content);

    rewind(content);
    fseek(content, 2, SEEK_SET); // Skip first two bytes
    fread(self->data + offset, size - 2, 1, content);
    fclose(content);
}