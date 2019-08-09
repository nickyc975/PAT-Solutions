#include <stdio.h>
#include <stdlib.h>

#define MAX_WIN_NUM 100
#define MAX_CUST_NUM 10000

typedef struct customer_struct
{
    int arrive_time;
    int process_time;
} customer_t;

int win_num, cust_num;
int windows[MAX_WIN_NUM];
customer_t customers[MAX_CUST_NUM];
const int eight = 8 * 3600, seventeen = 17 * 3600;

int cmp_cust(const void *a, const void *b)
{
    return ((customer_t *)a)->arrive_time - ((customer_t *)b)->arrive_time;
}

int main()
{
    int time = eight, wait_time = 0;

    scanf("%d %d", &cust_num, &win_num);
    for (int i = 0; i < win_num; i++)
    {
        windows[i] = 0;
    }

    int hour, minute, second;
    for (int i = 0; i < cust_num; i++)
    {
        scanf("%d:%d:%d %d", &hour, &minute, &second, &customers[i].process_time);
        customers[i].arrive_time = hour * 3600 + minute * 60 + second;
        customers[i].process_time *= 60;
    }

    qsort(customers, cust_num, sizeof(customer_t), cmp_cust);

    int i;
    for (i = 0; i < cust_num; i++)
    {
        if (customers[i].arrive_time > seventeen)
        {
            break;
        }

        if (customers[i].arrive_time > time)
        {
            int diff = customers[i].arrive_time - time;
            for (int j = 0; j < win_num; j++)
            {
                if (windows[j] < diff)
                {
                    windows[j] = 0;
                }
                else
                {
                    windows[j] -= diff;
                }
            }
            time = customers[i].arrive_time;
        }

        int win = 0, win_time;
        for (int j = 0; j < win_num; j++)
        {
            if (windows[j] < windows[win])
            {
                win = j;
            }
        }

        win_time = windows[win];
        time += win_time;
        for (int j = 0; j < win_num; j++)
        {
            windows[j] -= win_time;
        }

        wait_time += time - customers[i].arrive_time;
        windows[win] = customers[i].process_time;
    }

    printf("%.1f", (float)wait_time / (float)i / 60.0);

    return 0;
}