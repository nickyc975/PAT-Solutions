#include <stdio.h>
#include <stdlib.h>

int main()
{
    int length = 0;
    char ch, string[80];

    ch = getchar();
    while (ch != '\n' && ch != ' ')
    {
        string[length] = ch;
        ch = getchar();
        length++;
    }

    int remain = (length - 2) % 3;
    int h_length = (length - 2) / 3, v_length = h_length;
    if (remain == 1)
    {
        h_length++;
    }
    else if (remain == 2)
    {
        v_length++;
    }

    int start = 0, end = length - 1;
    while (start < v_length)
    {
        printf("%c", string[start++]);
        for (int i = 0; i < h_length; i++)
        {
            printf(" ");
        }
        printf("%c\n", string[end--]);
    }

    while (start <= end)
    {
        printf("%c", string[start++]);
    }
    
    return 0;
}