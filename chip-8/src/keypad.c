#include "keypad.h"

Key g_Keypad[KEY_COUNT];

void Keypad_Init()
{
    for (uint8_t i = 0; i < KEY_COUNT; ++i)
    {
        g_Keypad[i].isPressed = 0;
        g_Keypad[i].index = i;
    }
}

void Keypad_RegisterKeyState(SDL_Event e)
{
    if (e.type == SDL_KEYDOWN)
    {
        Keypad_SetKeyState(e.key.keysym.sym, 1);
    }
    else if (e.type == SDL_KEYUP)
    {
        Keypad_SetKeyState(e.key.keysym.sym, 0);
    }
}

void Keypad_SetKeyState(SDL_Keycode kc, uint8_t state)
{
    switch (kc)
    {
    case SDLK_1:
        g_Keypad[0].isPressed = state;
        break;
    case SDLK_2:
        g_Keypad[1].isPressed = state;
        break;
    case SDLK_3:
        g_Keypad[2].isPressed = state;
        break;
    case SDLK_4:
        g_Keypad[3].isPressed = state;
        break;
    case SDLK_q:
        g_Keypad[4].isPressed = state;
        break;
    case SDLK_w:
        g_Keypad[5].isPressed = state;
        break;
    case SDLK_e:
        g_Keypad[6].isPressed = state;
        break;
    case SDLK_r:
        g_Keypad[7].isPressed = state;
        break;
    case SDLK_a:
        g_Keypad[8].isPressed = state;
        break;
    case SDLK_s:
        g_Keypad[9].isPressed = state;
        break;
    case SDLK_d:
        g_Keypad[10].isPressed = state;
        break;
    case SDLK_f:
        g_Keypad[11].isPressed = state;
        break;
    case SDLK_z:
        g_Keypad[12].isPressed = state;
        break;
    case SDLK_x:
        g_Keypad[13].isPressed = state;
        break;
    case SDLK_c:
        g_Keypad[14].isPressed = state;
        break;
    case SDLK_v:
        g_Keypad[15].isPressed = state;
        break;
    default:
        break;
    }
}

Key Keypad_GetKey(uint8_t key)
{
    return g_Keypad[key];
}
