#include <cstdio>
#include <iostream>

using namespace std;

int node_cnt, bintree[1001];

void check()
{
    int status = 0;
    for (int i = 2; i <= node_cnt; i++)
    {
        if (bintree[i] > bintree[i / 2] && status <= 0)
        {
            status = -1;
        }
        else if (bintree[i] < bintree[i / 2] && status >= 0)
        {
            status = 1;
        }
        else
        {
            printf("Not Heap\n");
            return;
        }
    }
    printf(status > 0 ? "Max Heap\n" : "Min Heap\n");
    return;
}

void postorder(int root_idx)
{
    if (root_idx * 2 <= node_cnt)
    {
        postorder(root_idx * 2);
        printf(" ");
    }

    if ((root_idx * 2) + 1 <= node_cnt)
    {
        postorder((root_idx * 2) + 1);
        printf(" ");
    }

    printf("%d", bintree[root_idx]);
}

int main()
{
    int query_cnt;
    cin >> query_cnt >> node_cnt;
    for (int i = 0; i < query_cnt; i++)
    {
        for (int j = 1; j <= node_cnt; j++)
        {
            cin >> bintree[j];
        }
        check();
        postorder(1);
        printf("\n");
    }
    return 0;
}