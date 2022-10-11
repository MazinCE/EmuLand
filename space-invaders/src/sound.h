#ifndef SOUND_H
#define SOUND_H

#include "miniaudio.h"
#include <stdint.h>
#include <stdbool.h>

#define UFO             0
#define PLAYER_SHOT     1
#define PLAYER_DIED     2
#define INVADER_DIED    3
#define EXTENDED_PLAY   4
#define FLEET_MOVEMENT1 0
#define FLEET_MOVEMENT2 1
#define FLEET_MOVEMENT3 2
#define FLEET_MOVEMENT4 3
#define UFO_HIT         4

#define SOUND_GROUP1 3
#define SOUND_GROUP2 5

void Sound_Init(void);
void Sound_Destroy(void);
void Sound_Play(uint8_t soundGroup, uint8_t soundEventBits, uint8_t playingStatus);
bool Sound_CanPlay(uint8_t soundId, uint8_t soundEventBits, uint8_t playingStatus);

#endif