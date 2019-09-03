#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int vert_cnt, edge_cnt;
int vertices[1001], vert_copy[1001];
vector<int> edges[1001];

bool check(int seq[])
{
    memcpy(vert_copy, vertices, 1001 * sizeof(int));
    for (int i = 0; i < vert_cnt; i++)
    {
        if (vert_copy[seq[i]] != 0)
        {
            return false;
        }
        else
        {
            for (int j = 0; j < edges[seq[i]].size(); j++)
            {
                vert_copy[edges[seq[i]][j]]--;
            }
        }
    }
    return true;
}

int main()
{
    int source, target;
    cin >> vert_cnt >> edge_cnt;
    memset(vertices, 0, 1001 * sizeof(int));
    for (int i = 0; i < edge_cnt; i++)
    {
        cin >> source >> target;
        edges[source].push_back(target);
        vertices[target]++;
    }

    bool flag = false;
    int query_cnt, seq[1001];
    cin >> query_cnt;
    for (int i = 0; i < query_cnt; i++)
    {
        for (int j = 0; j < vert_cnt; j++)
        {
            cin >> seq[j];
        }
        if (!check(seq))
        {
            if (flag)
            {
                printf(" ");
            }
            else
            {
                flag = true;
            }
            printf("%d", i);
        }
    }

    return 0;
}