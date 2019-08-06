#include <stdio.h>
#include <stdlib.h>

int main()
{
    char result;
    double w_odd, t_odd, l_odd, max_odd, profit = 1.0;
    for (int i = 0; i < 3; i++)
    {
        scanf("%lf %lf %lf", &w_odd, &t_odd, &l_odd);
        if (t_odd > w_odd)
        {
            result = 'T';
            max_odd = t_odd;
        }
        else
        {
            result = 'W';
            max_odd = w_odd;
        }

        if (l_odd > max_odd)
        {
            result = 'L';
            max_odd = l_odd;
        }

        profit *= max_odd;
        printf("%c ", result);
    }
    profit = (profit * 0.65 - 1) * 2;
    printf("%.2lf", profit);
    return 0;
}