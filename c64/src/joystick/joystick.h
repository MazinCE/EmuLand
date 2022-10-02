#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

#define NUM_JOYSTICK 2
#define NUM_JOYStICK_BUTTONS 5

typedef struct
{
    uint8_t code;
    bool isDown;

} JoystickButton;

typedef struct
{
    SDL_GameController *gameController;
    JoystickButton joy[2][5];
    bool available;

} Joystick;

void Joystick_Init(void);
void Joystick_Destroy(void);
void Joystick_InitButtons(void);

void Joystick_RegisterButton(SDL_ControllerButtonEvent *e);
void Joystick_Emulate(void);
bool Joystick_Available(void);