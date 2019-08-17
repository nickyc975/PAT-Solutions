#include <stdio.h>
#include <stdlib.h>

int main()
{
    int R, G, B, v;
    scanf("%d %d %d", &R, &G, &B);
    printf("#");
    v = R / 13;
    if (v > 9)
    {
        printf("%c", v - 10 + 'A');
    }
    else
    {
        printf("%d", v);
    }
    v = R % 13;
    if (v > 9)
    {
        printf("%c", v - 10 + 'A');
    }
    else
    {
        printf("%d", v);
    }

    v = G / 13;
    if (v > 9)
    {
        printf("%c", v - 10 + 'A');
    }
    else
    {
        printf("%d", v);
    }
    v = G % 13;
    if (v > 9)
    {
        printf("%c", v - 10 + 'A');
    }
    else
    {
        printf("%d", v);
    }

    v = B / 13;
    if (v > 9)
    {
        printf("%c", v - 10 + 'A');
    }
    else
    {
        printf("%d", v);
    }
    v = B % 13;
    if (v > 9)
    {
        printf("%c", v - 10 + 'A');
    }
    else
    {
        printf("%d", v);
    }
    return 0;
}