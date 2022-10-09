#include "arcade.h"

// #include <stdio.h>
// #include "bus.h"

int main(void)
{
    Arcade_Init();
    Arcade_Run();
    Arcade_Destroy();

    // Bus_WritePort(SHFT_DATA, 0xaa);
    // Bus_WritePort(SHFT_DATA, 0xff);
    // Bus_WritePort(INP2_OR_SHFTAMNT, 3);
    // Bus_ReadPort(SHFT_IN);
    // Bus_ReadPort(SHFT_IN);
    // printf("%02X\n", g_bus.shiftReg);

    return 0;
}