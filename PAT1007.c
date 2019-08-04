#include <stdio.h>

int main()
{
    int length;
    int left = 0, right = 0, sum = -1;
    int temp_left = 0, temp_sum = temp_left;
    int first = 0, last = 0;

    int i = 0, value, updateLeft = 1;

    scanf("%d\n", &length);
    for (i = 0; i < length; i++)
    {
        scanf("%d", &value);

        if (i == 0)
        {
            first = value;
        }

        if (i == length - 1)
        {
            last = value;
        }

        if (updateLeft)
        {
            temp_left = value;
            updateLeft = 0;
        }

        temp_sum += value;
        if (temp_sum > sum)
        {
            sum = temp_sum;
            right = value;
            left = temp_left;
        }
        else if (temp_sum <= 0)
        {
            temp_sum = 0;
            updateLeft = 1;
        }
    }

    if (sum < 0)
    {
        printf("%d %d %d", 0, first, last);
    }
    else
    {
        printf("%d %d %d", sum, left, right);
    }

    return 0;
}