#include <cstdio>
#include <iostream>

using namespace std;

void reverse(int org[], int rev[], int len)
{
    for (int i = 0; i < len; i++)
    {
        rev[len - 1 - i] = org[i];
    }
}

void add(int org[], int rev[], int &len)
{
    int sum, remain = 0;
    for (int i = 0; i < len; i++)
    {
        sum = org[i] + rev[i] + remain;
        org[i] = sum % 10;
        remain = sum / 10;
    }

    if (remain > 0)
    {
        org[len] = remain;
        len++;
    }
}

bool is_palind(int num[], int len)
{
    for (int i = 0, j = len - 1; i < j; i++, j--)
    {
        if (num[i] != num[j])
        {
            return false;
        }
    }
    return true;
}

void print_num(int num[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%c", num[i] + '0');
    }
}

int main()
{
    int num_digits = 0;
    int original[1500], reversed[1500];

    char digit = getchar();
    while (digit >= '0' && digit <= '9')
    {
        reversed[num_digits++] = digit - '0';
        digit = getchar();
    }

    int count = 0;
    reverse(reversed, original, num_digits);
    while (!is_palind(original, num_digits) && count < 10)
    {
        print_num(reversed, num_digits);
        printf(" + ");
        print_num(original, num_digits);
        printf(" = ");

        add(original, reversed, num_digits);
        reverse(original, reversed, num_digits);

        print_num(reversed, num_digits);
        printf("\n");
        count++;
    }

    if (is_palind(original, num_digits))
    {
        print_num(reversed, num_digits);
        printf(" is a palindromic number.\n");
    }
    else
    {
        printf("Not found in 10 iterations.\n");
    }
    
    return 0;
}