#include "Keyboard.h"
#include "../c64bus.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

Keyboard g_Keyboard;

void Keyboard_Init(void)
{
    for (uint8_t i = 0; i < 64; ++i)
    {
        g_Keyboard.keyMatrix[i].isDown = false;
    }

    // Row 0
    g_Keyboard.keyMatrix[0].code = SDLK_BACKSPACE;
    g_Keyboard.keyMatrix[1].code = SDLK_RETURN;
    g_Keyboard.keyMatrix[2].code = SDLK_RIGHT;
    g_Keyboard.keyMatrix[3].code = SDLK_F7;
    g_Keyboard.keyMatrix[4].code = SDLK_F1;
    g_Keyboard.keyMatrix[5].code = SDLK_F3;
    g_Keyboard.keyMatrix[6].code = SDLK_F5;
    g_Keyboard.keyMatrix[7].code = SDLK_DOWN;

    // Row 1
    g_Keyboard.keyMatrix[8].code = SDLK_3;
    g_Keyboard.keyMatrix[9].code = SDLK_w;
    g_Keyboard.keyMatrix[10].code = SDLK_a;
    g_Keyboard.keyMatrix[11].code = SDLK_4;
    g_Keyboard.keyMatrix[12].code = SDLK_z;
    g_Keyboard.keyMatrix[13].code = SDLK_s;
    g_Keyboard.keyMatrix[14].code = SDLK_e;
    g_Keyboard.keyMatrix[15].code = SDLK_LSHIFT;

    // Row 2
    g_Keyboard.keyMatrix[16].code = SDLK_5;
    g_Keyboard.keyMatrix[17].code = SDLK_r;
    g_Keyboard.keyMatrix[18].code = SDLK_d;
    g_Keyboard.keyMatrix[19].code = SDLK_6;
    g_Keyboard.keyMatrix[20].code = SDLK_c;
    g_Keyboard.keyMatrix[21].code = SDLK_f;
    g_Keyboard.keyMatrix[22].code = SDLK_t;
    g_Keyboard.keyMatrix[23].code = SDLK_x;

    // Row 3
    g_Keyboard.keyMatrix[24].code = SDLK_7;
    g_Keyboard.keyMatrix[25].code = SDLK_y;
    g_Keyboard.keyMatrix[26].code = SDLK_g;
    g_Keyboard.keyMatrix[27].code = SDLK_8;
    g_Keyboard.keyMatrix[28].code = SDLK_b;
    g_Keyboard.keyMatrix[29].code = SDLK_h;
    g_Keyboard.keyMatrix[30].code = SDLK_u;
    g_Keyboard.keyMatrix[31].code = SDLK_v;

    // Row 4
    g_Keyboard.keyMatrix[32].code = SDLK_9;
    g_Keyboard.keyMatrix[33].code = SDLK_i;
    g_Keyboard.keyMatrix[34].code = SDLK_j;
    g_Keyboard.keyMatrix[35].code = SDLK_0;
    g_Keyboard.keyMatrix[36].code = SDLK_m;
    g_Keyboard.keyMatrix[37].code = SDLK_k;
    g_Keyboard.keyMatrix[38].code = SDLK_o;
    g_Keyboard.keyMatrix[39].code = SDLK_n;

    // Row 5
    g_Keyboard.keyMatrix[40].code = SDLK_EQUALS;
    g_Keyboard.keyMatrix[41].code = SDLK_p;
    g_Keyboard.keyMatrix[42].code = SDLK_l;
    g_Keyboard.keyMatrix[43].code = SDLK_MINUS;
    g_Keyboard.keyMatrix[44].code = SDLK_PERIOD;
    g_Keyboard.keyMatrix[45].code = SDLK_QUOTE;
    g_Keyboard.keyMatrix[46].code = SDLK_RIGHTBRACKET;
    g_Keyboard.keyMatrix[47].code = SDLK_COMMA;

    // Row 6
    g_Keyboard.keyMatrix[48].code = SDLK_BACKQUOTE;
    g_Keyboard.keyMatrix[49].code = SDLK_LEFTBRACKET;
    g_Keyboard.keyMatrix[50].code = SDLK_SEMICOLON;
    g_Keyboard.keyMatrix[51].code = SDLK_TAB;
    g_Keyboard.keyMatrix[52].code = SDLK_RSHIFT;
    g_Keyboard.keyMatrix[53].code = SDLK_BACKSLASH;
    g_Keyboard.keyMatrix[54].code = SDLK_UP;
    g_Keyboard.keyMatrix[55].code = SDLK_SLASH;

    // Row 7
    g_Keyboard.keyMatrix[56].code = SDLK_1;
    g_Keyboard.keyMatrix[57].code = SDLK_LEFT;
    g_Keyboard.keyMatrix[58].code = SDLK_LCTRL;
    g_Keyboard.keyMatrix[59].code = SDLK_2;
    g_Keyboard.keyMatrix[60].code = SDLK_SPACE;
    g_Keyboard.keyMatrix[61].code = SDLK_LALT;
    g_Keyboard.keyMatrix[62].code = SDLK_q;
    g_Keyboard.keyMatrix[63].code = SDLK_ESCAPE;
}

void Keyboard_RegisterKeyPress(SDL_KeyboardEvent *e)
{
    for (uint8_t i = 0; i < 64; ++i)
    {
        if (g_Keyboard.keyMatrix[i].code == (uint32_t)e->keysym.sym)
        {
            g_Keyboard.keyMatrix[i].isDown = e->state;
        }
    }
}

void Keyboard_Emulate(void)
{
    uint8_t row = C64Bus_ReadPort(CIA_ONE_PRA);
    uint8_t rowIndex = 0;
    uint8_t column = row ? 0xFF : 0x00;

    while (row & (1 << rowIndex))
    {
        rowIndex++;
    }

    if (rowIndex < 8)
    {
        for (uint8_t i = 0; i < 8; ++i)
        {
            if (g_Keyboard.keyMatrix[i + rowIndex * 8].isDown)
            {
                column &= ~(1 << i);
            }
        }
    }

    C64Bus_WritePort(CIA_ONE_PRB, column);
}
