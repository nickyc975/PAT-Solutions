#include <stdio.h>

using namespace std;

int main()
{
    int num, sum = 0;
    int last = 0, current, diff;

    scanf("%d", &num);
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &current);
        diff = current - last;
        if (diff > 0)
        {
            sum += diff * 6;
        }
        else
        {
            sum += -diff * 4;
        }
        sum += 5;
        last = current;
    }

    printf("%d", sum);

    return 0;
}