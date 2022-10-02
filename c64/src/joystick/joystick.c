#include "joystick.h"
#include <stdlib.h>
#include "../c64bus.h"

Joystick g_Joystick;

void Joystick_Init(void)
{
    SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);

    g_Joystick.available = false;

    g_Joystick.gameController = SDL_GameControllerOpen(0);

    if (g_Joystick.gameController != NULL)
    {
        g_Joystick.available = true;

        Joystick_InitButtons();
    }
}

void Joystick_Destroy(void)
{
    SDL_GameControllerClose(g_Joystick.gameController);
}

void Joystick_InitButtons(void)
{
    for (uint8_t i = 0; i < NUM_JOYSTICK; ++i)
    {
        for (uint8_t j = 0; j < NUM_JOYStICK_BUTTONS; ++j)
        {
            g_Joystick.joy[i][j].isDown = false;
        }
    }

    g_Joystick.joy[0][0].code = SDL_CONTROLLER_BUTTON_Y;
    g_Joystick.joy[0][1].code = SDL_CONTROLLER_BUTTON_A;
    g_Joystick.joy[0][2].code = SDL_CONTROLLER_BUTTON_X;
    g_Joystick.joy[0][3].code = SDL_CONTROLLER_BUTTON_B;
    g_Joystick.joy[0][4].code = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;

    g_Joystick.joy[1][0].code = SDL_CONTROLLER_BUTTON_DPAD_UP;
    g_Joystick.joy[1][1].code = SDL_CONTROLLER_BUTTON_DPAD_DOWN;
    g_Joystick.joy[1][2].code = SDL_CONTROLLER_BUTTON_DPAD_LEFT;
    g_Joystick.joy[1][3].code = SDL_CONTROLLER_BUTTON_DPAD_RIGHT;
    g_Joystick.joy[1][4].code = SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
}

void Joystick_RegisterButton(SDL_ControllerButtonEvent *e)
{
    for (uint8_t i = 0; i < 2; ++i)
    {
        for (uint8_t j = 0; j < 5; ++j)
        {
            if (g_Joystick.joy[i][j].code == e->button)
            {
                g_Joystick.joy[i][j].isDown = e->type == SDL_CONTROLLERBUTTONDOWN;
            }
        }
    }
}

void Joystick_Emulate(void)
{
    for (uint8_t i = 0; i < NUM_JOYSTICK; ++i)
    {
        uint8_t buttons = C64Bus_ReadPort((C64BusPortType)(CIA_ONE_PRA + i));

        for (uint8_t j = 0; j < 5; ++j)
        {
            if (g_Joystick.joy[i][j].isDown)
            {
                buttons &= ~(1 << j);
            }
        }

        C64Bus_WritePort((C64BusPortType)(CIA_ONE_PRA + i), buttons);
    }
}

bool Joystick_Available(void)
{
    return g_Joystick.available;
}