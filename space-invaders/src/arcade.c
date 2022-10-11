#include "arcade.h"
#include "bus.h"
#include "cpu.h"
#include "display.h"
#include <unistd.h>

Arcade g_Arcade;

void Arcade_Init(void)
{
    Bus_Init();
    CPU_Init();
#if !CPUDIAG
    Display_Init();
#endif

    g_Arcade.frameElapsedTime = 0.0f;
    g_Arcade.interrputNum = 0;
    g_Arcade.running = true;
    g_Arcade.frameHalfCycles = 0;
    g_Arcade.lastUpdate = clock();

}

void Arcade_Destroy(void)
{
    Bus_Destroy();
#if !CPUDIAG
    Display_Destroy();
#endif
}

void Arcade_ReadInput(SDL_Event e)
{
    uint8_t port1 = Bus_ReadPort(INP1);
    uint8_t port2 = Bus_ReadPort(INP2_OR_SHFTAMNT);

    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_c:
            port1 |= (1 << INSERT_COIN);
            break;
        case SDLK_1:
            port1 |= (1 << BTN_1PLAYER);
            break;
        case SDLK_2:
            port1 |= (1 << BTN_2PLAYERS);
            break;
        case SDLK_3:
            port2 |= (1 << DIP_NUM_SHIPS_B0);
            break;
        case SDLK_4:
            port2 |= (1 << DIP_NUM_SHIPS_B1);
            break;
        case SDLK_5:
            port2 |= (1 << DIP_DIFFICULTY);
            break;
        case SDLK_6:
            port2 |= (1 << DIP_COIN_INFO);
            break;
        case SDLK_a:
            port1 |= (1 << BTN_P1_LEFT);
            break;
        case SDLK_d:
            port1 |= (1 << BTN_P1_RIGHT);
            break;
        case SDLK_w:
            port1 |= (1 << BTN_P1_FIRE);
            break;
        case SDLK_LEFT:
            port2 |= (1 << BTN_P2_LEFT);
            break;
        case SDLK_RIGHT:
            port2 |= (1 << BTN_P2_RIGHT);
            break;
        case SDLK_UP:
            port2 |= (1 << BTN_P2_FIRE);
            break;
        default:
            break;
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_c:
            port1 &= ~(1 << INSERT_COIN);
            break;
        case SDLK_1:
            port1 &= ~(1 << BTN_1PLAYER);
            break;
        case SDLK_2:
            port1 &= ~(1 << BTN_2PLAYERS);
            break;
        case SDLK_3:
            port2 &= ~(1 << DIP_NUM_SHIPS_B0);
            break;
        case SDLK_4:
            port2 &= ~(1 << DIP_NUM_SHIPS_B1);
            break;
        case SDLK_5:
            port2 &= ~(1 << DIP_DIFFICULTY);
            break;
        case SDLK_6:
            port2 &= ~(1 << DIP_COIN_INFO);
            break;
        case SDLK_a:
            port1 &= ~(1 << BTN_P1_LEFT);
            break;
        case SDLK_d:
            port1 &= ~(1 << BTN_P1_RIGHT);
            break;
        case SDLK_w:
            port1 &= ~(1 << BTN_P1_FIRE);
            break;
        case SDLK_LEFT:
            port2 &= ~(1 << BTN_P2_LEFT);
            break;
        case SDLK_RIGHT:
            port2 &= ~(1 << BTN_P2_RIGHT);
            break;
        case SDLK_UP:
            port2 &= ~(1 << BTN_P2_FIRE);
            break;
        default:
            break;
        }
    }

    Bus_SetInputPort(INP1, port1);
    Bus_SetInputPort(INP2_OR_SHFTAMNT, port2);
}

void Arcade_Run(void)
{
    SDL_Event e;

    while (g_Arcade.running)
    {
        clock_t now = clock();

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                g_Arcade.running = false;
            }
            else
            {
                Arcade_ReadInput(e);
            }
        }

        if (g_Arcade.frameElapsedTime >= ARCADE_MS_PERFRAME)
        {
            CPU_ResetTicks();
            g_Arcade.frameHalfCycles = 0;

            while (CPU_GetCycles() < ARCADE_TICKS_PER_FRAME)
            {
                CPU_Tick();

                if (CPU_GetCycles() - g_Arcade.frameHalfCycles >= ARCADE_TICKS_PER_HALF_FRAME)
                {
                    CPU_Interrupt(g_Arcade.interrputNum);
                    g_Arcade.interrputNum = g_Arcade.interrputNum == 1 ? 2 : 1;
                    g_Arcade.frameHalfCycles = CPU_GetCycles();
                }
            }

            Arcade_Display();

            g_Arcade.frameElapsedTime = 0.0f;
            g_Arcade.lastUpdate = clock();
        }

        g_Arcade.frameElapsedTime += (float)(now - g_Arcade.lastUpdate) / ARCADE_TICKS_PER_FRAME;
    }
}

void Arcade_Display(void)
{
    Display_ClearFrameBuffer();

    for (uint8_t y = 0; y < ARCADE_WINDOW_HEIGHT; ++y)
    {
        for (uint8_t x = 0; x < (ARCADE_WINDOW_WIDTH / 8); ++x)
        {
            uint8_t sprite = Bus_ReadMemory(0x2400 + (x + y * (ARCADE_WINDOW_WIDTH / 8)));

            for (uint8_t i = 0; i < 8; ++i)
            {
                if (sprite & (1 << i))
                {
                    Display_SetPixel(8 * x + i, y);
                }
            }
        }
    }

    Display_Render();
}
