#include <stdio.h>

int check_parity(int n)
{
    int p = 0;

    for (int i = 0; i < 8; ++i)
    {
        p ^= 1 & (n >> i);
    }

    return p;
}

int main(void)
{
    printf("%d\n", check_parity(8));

    return 0;
}