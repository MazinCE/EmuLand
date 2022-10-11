#define MINIAUDIO_IMPLEMENTATION
// #include "arcade.h"
#include "miniaudio.h"

#include "arcade.h"

int main(void)
{
    Arcade_Init();
    Arcade_Run();
    Arcade_Destroy();

    return 0;
}