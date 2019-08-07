#include <math.h>
#include <stdio.h>

int is_prime(int value);
int reverse(int value, int radix);

int main()
{
    int value, radix;
    scanf("%d", &value);
    while (value > 0)
    {
        scanf("%d", &radix);
        int reversed = reverse(value, radix);
        if (is_prime(value) && is_prime(reversed))
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
        scanf("%d", &value);
    }
    return 0;
}

int is_prime(int value)
{
    if (value <= 1)
    {
        return 0 ;
    }

    int factor = (int)sqrt((double)value) + 1;
    while (factor < value && factor > 1)
    {
        if (value % factor == 0)
        {
            return 0;
        }
        factor--;
    }
    return 1;
}

int reverse(int value, int radix)
{
    int result = 0;
    while (value > 0)
    {
        result = result * radix + value % radix;
        value /= radix;
    }
    return result;
}