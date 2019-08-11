#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned long long temp, value;
    int value_d[10] = {0}, doubled_d[10] = {0};
    scanf("%llu", &value);

    if (value == 0)
    {
        printf("Yes\n%llu", value);
        return 0;
    }

    temp = value;
    while (temp > 0)
    {
        value_d[temp % 10]++;
        temp /= 10;
    }

    temp = value * 2;
    while (temp > 0)
    {
        doubled_d[temp % 10]++;
        temp /= 10;
    }
    
    for (int i = 0; i < 10; i++)
    {
        if (value_d[i] != doubled_d[i])
        {
            printf("No\n%llu", value * 2);
            return 0;
        }
    }

    printf("Yes\n%llu", value * 2);
    return 0;
}