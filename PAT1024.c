#include <stdio.h>
#include <stdlib.h>

int is_palindromic(char value[], int value_len)
{
    for (int i = 0, j = value_len - 1; i < value_len; i++, j--)
    {
        if (value[i] != value[j])
        {
            return 0;
        }
    }
    return 1;
}

void reverse(char value[], char reversed[], int value_len)
{
    for (int i = 0; i < value_len; i++)
    {
        reversed[value_len - i - 1] = value[i];
    }
}

int add_to(char dest[], char value[], int len)
{
    int sum, carry = 0;
    for (int i = 0; i < len; i++)
    {
        sum = dest[i] + value[i] + carry;
        dest[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry > 0)
    {
        dest[len] = carry;
        len++;
    }
    return len;
}

int main()
{
    char original[100], reversed[100];
    int steps = 0, max_step, length = 0;

    char ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        reversed[length] = ch - '0';
        ch = getchar();
        length++;
    }
    reverse(reversed, original, length);
    scanf("%d", &max_step);

    while (steps < max_step && !is_palindromic(original, length))
    {
        reverse(original, reversed, length);
        length = add_to(original, reversed, length);
        steps++;
    }

    for (int i = length - 1; i >= 0; i--)
    {
        printf("%d", original[i]);
    }
    printf("\n%d", steps);
    return 0;
}