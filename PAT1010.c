#include <stdio.h>
#include <stdlib.h>

int value_of(char *digits, int length, int radix);

int main()
{
    char ch, a[11], b[11], *c;
    int a_len = 0, b_len = 0, c_len, tag, radix, value;

    while ((ch = getchar()) != ' ')
    {
        a[a_len] = ch;
        a_len++;
    }
    a[a_len] = 0;

    while ((ch = getchar()) != ' ')
    {
        b[b_len] = ch;
        b_len++;
    }
    b[b_len] = 0;

    scanf("%d %d", tag, radix);

    if (tag == 1)
    {
        value = value_of(a, a_len, radix);
        c_len = b_len;
        c = b;
    }
    else
    {
        value = value_of(b, b_len, radix);
        c_len = a_len;
        c = a;
    }
    
    // TODO: check impossible.

    return 0;
}

int value_of(char *digits, int length, int radix)
{
    char digit;
    int index = length - 1;
    int value = 0, exp = 1, digit_val;

    while (index >= 0)
    {
        digit = digits[index];
        if (digit >= '0' && digit <= '9')
        {
            digit_val = digit - '0';
        }
        else
        {
            digit_val = digit - 'a' + 10;
        }

        if (digit_val >= radix || digit_val < 0)
        {
            return -1;
        }
        value += digit_val * exp;
        exp *= radix;
        index--;
    }
    
    return value;
}