#include <stdio.h>
#include <stdlib.h>

int main()
{
    char value[25], doubled[25];
    int i, val_d_num = 0, dbld_d_num = 0;
    char value_d[10] = {0}, doubled_d[10] = {0};

    char ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        value[val_d_num] = ch - '0';
        ch = getchar();
        val_d_num++;
    }

    for (i = val_d_num - 1, ch = 0; i >= 0; i--)
    {
        ch += value[i] * 2;
        doubled[dbld_d_num] = ch % 10;
        dbld_d_num++;
        ch /= 10;
    }

    if (ch > 0)
    {
        doubled[dbld_d_num] = ch % 10;
        dbld_d_num++;
    }

    if (dbld_d_num != val_d_num)
    {
        printf("No\n");
    }
    else
    {
        for (i = 0; i < val_d_num; i++)
        {
            value_d[value[i]]++;
            doubled_d[doubled[i]]++;
        }
        
        for (i = 0; i < 10; i++)
        {
            if (value_d[i] != doubled_d[i])
            {
                printf("No\n");
                break;
            }
        }

        if (i >= 10)
        {
            printf("Yes\n");
        }
    }

    while (dbld_d_num > 0)
    {
        printf("%d", doubled[dbld_d_num - 1]);
        dbld_d_num--;
    }
    return 0;
}