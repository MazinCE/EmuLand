#include "arcade.h"
#include "bus.h"
#include "cpu.h"
#include "display.h"
#include <time.h>
#include <unistd.h>

void Arcade_Init(void)
{
    Bus_Init();
    CPU_Init();
    Display_Init();

    Display_SetPixel(4, 6);
}

void Arcade_Destroy(void)
{
    Bus_Destroy();
    Display_Destroy();
}

void Arcade_ReadInput(SDL_Event e)
{
    uint8_t port1 = Bus_ReadPort(INP1);
    uint8_t port2 = Bus_ReadPort(INP2_OR_SHFTAMNT);

    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_RETURN:
            port1 |= (1 << 2);
            break;
        case SDLK_a:
            port1 |= (1 << 5);
            break;
        case SDLK_d:
            port1 |= (1 << 6);
            break;
        case SDLK_t:
            port2 |= (1 << 2);
            break;
        case SDLK_c:
            port1 |= (1 << 0);
            break;
        case SDLK_SPACE:
            port1 |= (1 << 4);
            break;
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_RETURN:
            port1 &= ~(1 << 2);
            break;
        case SDLK_a:
            port1 &= ~(1 << 5);
            break;
        case SDLK_d:
            port1 &= ~(1 << 6);
            break;
        case SDLK_t:
            port2 &= ~(1 << 2);
            break;
        case SDLK_c:
            port1 &= ~(1 << 0);
            break;
        case SDLK_SPACE:
            port1 &= ~(1 << 4);
            break;
        }
    }

    Bus_WritePort(INP1, port1);
    Bus_WritePort(INP2_OR_SHFTAMNT, port2);
}

void Arcade_Run(void)
{
    bool quit = false;
    SDL_Event e;
    float dt = 0;

    clock_t last, now;

    last = clock();

    while (!quit)
    {
        now = clock();
        dt += (float)(now - last) / ARCADE_TICKS_PERFRAME;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else
            {
                Arcade_ReadInput(e);
            }
        }

        if (dt > ARCADE_MS_PERFRAME)
        {
            dt = 0.0f;
            last = now;

            CPU_ResetTicks();

            while (CPU_Tick() < ARCADE_TICKS_PERFRAME)
                ;
            Arcade_Draw();
        }
    }
}

void Arcade_Draw(void)
{
    for (uint8_t y = 0; y < ARCADE_WINDOW_HEIGHT; ++y)
    {
        for (uint8_t x = 0; x < ARCADE_WINDOW_WIDTH / 8; ++x)
        {
            uint8_t sprite = Bus_ReadMemory(0x2400 + (x + y * 32));

            for (uint8_t i = 0; i < 8; ++i)
            {
                if (sprite & (1 << i))
                {
                    Display_SetPixel(ARCADE_WINDOW_WIDTH - (8 * x + i), y);
                }
            }
        }
    }
}
