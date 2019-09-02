#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    int num_palyers, palyers[101];
    int is_wolf[101], liars[101], liar_cnt;
    
    for (int i = 0; i < 101; i++)
    {
        is_wolf[i] = 1;
    }

    cin >> num_palyers;
    for (int i = 1; i <= num_palyers; i++)
    {
        cin >> palyers[i];
    }

    for (int i = 1; i < num_palyers; i++)
    {
        is_wolf[i] = -1;
        for (int j = i + 1; j <= num_palyers; j++)
        {
            is_wolf[j] = -1;

            liar_cnt = 0;
            for (int k = 1; k <= num_palyers; k++)
            {
                if (palyers[k] * is_wolf[abs(palyers[k])] < 0)
                {
                    liars[liar_cnt++] = k;
                }
            }
            if (liar_cnt == 2 && (is_wolf[liars[0]] + is_wolf[liars[1]]) == 0)
            {
                printf("%d %d", i, j);
                return 0;
            }

            is_wolf[j] = 1;
        }
        is_wolf[i] = 1;
    }
    printf("No Solution");
    return 0;
}