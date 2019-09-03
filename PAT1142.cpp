#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <vector>

#define MAX_VERT_NUM 210

using namespace std;

int vert_num;
vector<int> vertices;
int edges[MAX_VERT_NUM][MAX_VERT_NUM];

void check()
{
    bool exists[MAX_VERT_NUM] = {false};
    for (int i = 0; i < vertices.size(); i++)
    {
        exists[vertices[i]] = true;
        for (int j = i + 1; j < vertices.size(); j++)
        {
            if (edges[vertices[i]][vertices[j]] == 0)
            {
                printf("Not a Clique\n");
                return;
            }
        }
    }

    for (int i = 1; i <= vert_num; i++)
    {
        if (!exists[i])
        {
            int j = 0;
            for (j = 0; j < vertices.size(); j++)
            {
                if (edges[i][vertices[j]] == 0)
                {
                    break;
                }
            }

            if (j >= vertices.size())
            {
                printf("Not Maximal\n");
                return;
            }
        }
    }
    printf("Yes\n");
}

int main()
{
    int edge_num;
    cin >> vert_num >> edge_num;

    int source, target;
    for (int i = 0; i < edge_num; i++)
    {
        cin >> source >> target;
        edges[source][target] = 1;
        edges[target][source] = 1;
    }

    int query_num, num, vert;
    cin >> query_num;
    for (int i = 0; i < query_num; i++)
    {
        cin >> num;
        for (int j = 0; j < num; j++)
        {
            cin >> vert;
            vertices.push_back(vert);
        }
        check();
        vertices.clear();
    }
    return 0;
}