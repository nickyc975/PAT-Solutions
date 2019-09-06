#include <cstring>
#include <iostream>

using namespace std;

int vertices[256] = {0};
int edges[256][256] = {0};

int main()
{
    int vert_num, edge_num;
    cin >> vert_num >> edge_num;

    int source, target;
    for (int i = 0; i < edge_num; i++)
    {
        cin >> source >> target;
        edges[source][target] = 1;
        edges[target][source] = 1;
    }

    bool flag;
    int query_num, path_len, vert, prev_vert, start;

    cin >> query_num;
    for (int i = 0; i < query_num; i++)
    {
        cin >> path_len >> start;
        flag = path_len == (vert_num + 1);

        prev_vert = start;
        for (int j = 1; j < path_len; j++)
        {
            cin >> vert;
            if (flag)
            {
                if (vertices[vert] == 1 || edges[vert][prev_vert] == 0)
                {
                    flag = false;
                }
                else
                {
                    vertices[vert] = 1;
                }
            }
            prev_vert = vert;
        }

        printf(flag && vert == start ? "YES\n" : "NO\n");
        memset(vertices, 0, 256 * sizeof(int));
    }
    return 0;
}