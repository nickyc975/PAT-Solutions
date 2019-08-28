#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_prime(int value)
{
    if (value < 2)
    {
        return 0;
    }

    if (value == 2)
    {
        return 1;
    }

    int bound = (int)sqrt(value) + 1;
    for (int i = 2; i <= bound; i++)
    {
        if (value % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int l, k;
    char number[10], digits[1005];

    scanf("%d %d\n", &l, &k);
    for (int i = 0; i < l; i++)
    {
        digits[i] = getchar();
    }

    for (int i = 0; i < l - k + 1; i++)
    {
        number[k] = 0;
        memcpy(number, digits + i, k);
        if (is_prime(atoi(number)))
        {
            printf("%s", number);
            return 0;
        }
    }

    printf("404");
    return 0;
}