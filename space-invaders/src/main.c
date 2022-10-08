#include "arcade.h"
#include "register_file.h"
#include <stdio.h>

int main(void)
{
    Arcade_Init();
    Arcade_Run();
    Arcade_Destroy();

    return 0;
}