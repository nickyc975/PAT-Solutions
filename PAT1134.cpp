#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int vert_num, edge_num;
    int vertices[10000] = {0};
    vector<pair<int, int> *> edges;

    int source, target;
    cin >> vert_num >> edge_num;
    for (int i = 0; i < edge_num; i++)
    {
        cin >> source >> target;
        edges.push_back(new pair<int, int>(source, target));
    }

    int query_num;
    cin >> query_num;
    for (int i = 0; i < query_num; i++)
    {
        int v_num;
        cin >> v_num;
        for (int j = 0; j < v_num; j++)
        {
            int vert;
            cin >> vert;
            vertices[vert] = 1;
        }

        bool flag = true;
        for (pair<int, int> *edge : edges)
        {
            if (vertices[edge->first] == 0 && vertices[edge->second] == 0)
            {
                flag = false;
                break;
            }
        }
        memset(vertices, 0, 10000 * sizeof(int));
        printf(flag ? "Yes\n" : "No\n");
    }
    return 0;
}