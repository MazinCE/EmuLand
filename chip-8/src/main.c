#include "../include/chip8.h"

#include <time.h>

int main(int argc, char **args)
{
    if (argc < 3)
    {
        printf("Please select a rom and configure emulator speed...\n");
        return 0;
    }

    Chip8_Init();

    int quit = Chip8_LoadRom(args[1]) == -1;

    uint8_t cycleDelay = atoi(args[2]);

    clock_t last, current;
    float dt = 0;

    last = clock();
    
    SDL_Event e;

    while (!quit)
    {
        current = clock();
        dt += (float)(current - last) / CLOCKS_PER_SEC;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
            else
            {
                Chip8_HandleInput(e);
            }
        }

        if (dt > 16.67f)
        {
            Chip8_Tick(cycleDelay);
            Chip8_Draw();
            last = current;
            dt = 0.0f;
        }
    }

    Chip8_Destory();
    return 0;
}