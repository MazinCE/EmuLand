#include "C64.h"
#include "c64bus.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <unistd.h>

 bool g_C64_running;

void C64_Init(void)
{
    C64Bus_Init();
    Keyboard_Init();
    Joystick_Init();
    Display_Init();

   g_C64_running = true;
}

void C64_Destroy(void)
{
    C64Bus_Destroy();
    Joystick_Destroy();
    Display_Distroy();
}

void C64_Run(void)
{
    float dt = 0.0F;

    while (g_C64_running)
    {
        uint64_t start = SDL_GetPerformanceCounter();
        C64_HandleWindowEvents();

        if (dt >= 0.02F)
        {
            for (uint32_t i = 0; i < PAL_CYCLES_PER_FRAME; ++i)
            {
                C64Bus_Tick();
                Keyboard_Emulate();

                if (Joystick_Available())
                {
                    Joystick_Emulate();
                }
            }

            Display_Render();
            dt = 0.0F;
        }

        dt += (SDL_GetPerformanceCounter() - start) / (float)SDL_GetPerformanceFrequency();
    }
}

void C64_HandleWindowEvents(void)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            g_C64_running = false;
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (e.key.keysym.sym == SDLK_INSERT && e.key.state == 0)
            {
                C64_LoadPRG("../assets/karate.prg", 0x801);
            }
            Keyboard_RegisterKeyPress(&e.key);
            break;
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
            Joystick_RegisterButton(&e.cbutton);
            break;
        };
    }
}

void C64_LoadPRG(const char *path, uint16_t offset)
{
    if (access(path, F_OK) == -1)
    {
        printf("Unable to load prg file...\n");
    }
    else
    {
        Memory_LoadPRG(C64Bus_GetRAM(), offset, path);
        printf("prg file Loaded...\n");
    }
}
