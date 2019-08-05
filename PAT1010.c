#include <stdio.h>
#include <stdlib.h>

int min_radix(char *digits, int length);

unsigned long long value_of(char *digits, int length, unsigned int radix);

int main()
{
    char ch, a[11], b[11], *c;
    int a_len = 0, b_len = 0, c_len, tag;
    unsigned int radix, c_radix;
    unsigned long long value, c_value;

    ch = getchar();
    while (ch != ' ')
    {
        a[a_len] = ch;
        a_len++;

        ch = getchar();
    }
    a[a_len] = 0;

    ch = getchar();
    while (ch != ' ')
    {
        b[b_len] = ch;
        b_len++;

        ch = getchar();
    }
    b[b_len] = 0;

    scanf("%d %d", &tag, &radix);

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

    c_radix = min_radix(c, c_len);
    c_value = value_of(c, c_len, c_radix);

    if (c_len > 1)
    {
        while (c_value < value)
        {
            c_radix *= 2;
            c_value = value_of(c, c_len, c_radix);
        }

        if (c_value > value)
        {
            unsigned int high = c_radix;
            unsigned int low = c_radix / 2;
            while (high - low > 1)
            {
                c_radix = low + (high - low) / 2;
                c_value = value_of(c, c_len, c_radix);

                if (c_value < value)
                {
                    low = c_radix;
                }
                else if (c_value > value)
                {
                    high = c_radix;
                }
                else
                {
                    break;
                }
            }

            while (low <= high && c_value != value)
            {
                c_radix = low;
                c_value = value_of(c, c_len, c_radix);
                low++;
            }
        }
    }

    if (c_value == value)
    {
        printf("%d", c_radix);
    }
    else
    {
        printf("Impossible");
    }

    return 0;
}

int min_radix(char *digits, int length)
{
    char digit;
    int index = length - 1, radix = 2, digit_val;
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

        if (digit_val >= radix)
        {
            radix = digit_val + 1;
        }
        index--;
    }
    return radix;
}

unsigned long long value_of(char *digits, int length, unsigned int radix)
{
    char digit;
    int index = length - 1;
    unsigned long long value = 0, exp = 1, digit_val;

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
            return 0;
        }
        value += digit_val * exp;
        exp *= radix;
        index--;
    }

    return value;
}