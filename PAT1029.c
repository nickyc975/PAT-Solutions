#include <stdio.h>
#include <stdlib.h>

int int_seq[200000];

int main()
{
    int num_1, num_2;
    scanf("%d", &num_1);
    for (int i = 0; i < num_1; i++)
    {
        scanf(" %d", &int_seq[i]);
    }
    scanf("%d", &num_2);
    int value, count = 0, cursor = 0;
    int half = (num_1 + num_2 + 1) / 2;
    for (int i = 0; i < num_2; i++)
    {
        scanf(" %d", &value);
        while (count < half && cursor < num_1 && value > int_seq[cursor])
        {
            count++;
            cursor++;
        }
        
        if (count == half)
        {
            printf("%ld\n", int_seq[cursor - 1]);
            return 0;
        }
        count++;
        if (count == half)
        {
            printf("%ld\n", value);
            return 0;
        }
    }
    
    while (count < half)
    {
        count++;
        cursor++;
    }
    printf("%ld\n", int_seq[cursor - 1]);

    return 0;
}