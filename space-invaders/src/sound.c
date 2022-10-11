#include "sound.h"

ma_engine g_AudioEngine;

void Sound_Init(void)
{
    ma_engine_init(NULL, &g_AudioEngine);
}

void Sound_Destroy(void)
{
    ma_engine_uninit(&g_AudioEngine);
}

void Sound_Play(uint8_t soundGroup, uint8_t soundEventBits, uint8_t playingStatus)
{
    switch (soundGroup)
    {
    case SOUND_GROUP1:
        if (Sound_CanPlay(UFO, soundEventBits, playingStatus))
        {
            ma_engine_play_sound(&g_AudioEngine, "../sound/8.wav", NULL);
        }

        if (Sound_CanPlay(PLAYER_SHOT, soundEventBits, playingStatus))
        {
            ma_engine_play_sound(&g_AudioEngine, "../sound/3.wav", NULL);
        }

        if (Sound_CanPlay(PLAYER_DIED, soundEventBits, playingStatus))
        {
            ma_engine_play_sound(&g_AudioEngine, "../sound/2.wav", NULL);
        }

        if (Sound_CanPlay(INVADER_DIED, soundEventBits, playingStatus))
        {
            ma_engine_play_sound(&g_AudioEngine, "../sound/1.wav", NULL);
        }

        if (Sound_CanPlay(EXTENDED_PLAY, soundEventBits, playingStatus))
        {
            ma_engine_play_sound(&g_AudioEngine, "../sound/9.wav", NULL);
        }
        break;
    case SOUND_GROUP2:
        if (Sound_CanPlay(FLEET_MOVEMENT1, soundEventBits, playingStatus))
        {
            ma_engine_play_sound(&g_AudioEngine, "../sound/4.wav", NULL);
        }

        if (Sound_CanPlay(FLEET_MOVEMENT2, soundEventBits, playingStatus))
        {
            ma_engine_play_sound(&g_AudioEngine, "../sound/5.wav", NULL);
        }

        if (Sound_CanPlay(FLEET_MOVEMENT3, soundEventBits, playingStatus))
        {
            ma_engine_play_sound(&g_AudioEngine, "../sound/6.wav", NULL);
        }

        if (Sound_CanPlay(FLEET_MOVEMENT4, soundEventBits, playingStatus))
        {
            ma_engine_play_sound(&g_AudioEngine, "../sound/7.wav", NULL);
        }
        
        if (Sound_CanPlay(UFO_HIT, soundEventBits, playingStatus))
        {
            ma_engine_play_sound(&g_AudioEngine, "../sound/0.wav", NULL);
        }
        break;
    default:
        break;
    }
}

bool Sound_CanPlay(uint8_t soundId, uint8_t soundEventBits, uint8_t playingStatus)
{
    return (soundEventBits & (1 << soundId)) && (playingStatus & (1 << soundId)) == 0;
}