#ifndef ARCADE_H
#define ARCADE_H

#include <SDL2/SDL.h>

enum ArcadePort1
{
    INSERT_COIN  = 0,
    BTN_2PLAYERS = 1,
    BTN_1PLAYER  = 2,
    BTN_P1_FIRE  = 4,
    BTN_P1_LEFT  = 5,
    BTN_P1_RIGHT = 6,
};

enum ArcadePort2
{
    DIP_NUM_SHIPS_B0 = 0,
    DIP_NUM_SHIPS_B1 = 1,
    DIP_DIFFICULTY   = 2,
    BTN_P2_FIRE      = 4,
    BTN_P2_LEFT      = 5,
    BTN_P2_RIGHT     = 6,
    DIP_COIN_INFO    = 7,
};

enum ArcadePort3
{
    SND_SPACESHIP = 0,
    SND_SHOT,
    SND_PLAYER_HIT,
    SND_INVADER_HIT,
    SND_EXTENDED_PLAY,
};

enum ArcadePort5
{
    SND_INVADER_WALK1 = 0,
    SND_INVADER_WALK2,
    SND_INVADER_WALK3,
    SND_INVADER_WALK4,
    SND_SPACESHIP_HIT,
};

#define ARCADE_TICKS_PER_FRAME 33333
#define ARCADE_TICKS_PER_HALF_FRAME 16666
#define ARCADE_MS_PERFRAME 16.67f

void Arcade_Init(void);
void Arcade_Destroy(void);
void Arcade_ReadInput(SDL_Event e);
void Arcade_Run(void);
void Arcade_Display(void);

#endif