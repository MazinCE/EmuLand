#include <stdint.h>
#include <SDL2/SDL.h>

#define KEY_COUNT 16

typedef struct
{
    uint8_t index;
    uint8_t isPressed;
} Key;

void Keypad_Init();

void Keypad_RegisterKeyState(SDL_Event e);
void Keypad_SetKeyState(SDL_Keycode kc, uint8_t state);
Key Keypad_GetKey(uint8_t key);