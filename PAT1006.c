#include <stdio.h>
#include <string.h>

int main()
{
    char unlocked[16], locked[16];
    int num, unlocked_time = 0x7FFFFFFF, locked_time = 0;

    char id[16];
    int in_time, in_hour, in_minute, in_second;
    int out_time, out_hour, out_minute, out_second;

    int i;
    scanf("%d\n", &num);
    for (i = 0; i < num; i++)
    {
        scanf("%s %d:%d:%d %d:%d:%d", id, &in_hour, &in_minute, &in_second, &out_hour, &out_minute, &out_second);
        
        in_time = in_hour * 3600 + in_minute * 60 + in_second;
        if (in_time < unlocked_time) {
            strcpy(unlocked, id);
            unlocked_time = in_time;
        }

        out_time = out_hour * 3600 + out_minute * 60 + out_second;
        if (out_time > locked_time) {
            strcpy(locked, id);
            locked_time = out_time;
        }
    }

    printf("%s %s", unlocked, locked);

    return 0;
}