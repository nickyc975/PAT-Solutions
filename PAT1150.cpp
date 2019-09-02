#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

#define MAX_VERT_NUM 201

using namespace std;

int vertices[MAX_VERT_NUM];
int edges[MAX_VERT_NUM][MAX_VERT_NUM];

int vert_num, edge_num;
int min_path, min_dist = INT32_MAX;

void follow_path(vector<int> &path)
{
    int distance = 0;
    memset(vertices, 0, MAX_VERT_NUM * sizeof(int));

    vertices[path[1]]++;
    for (int i = 2; i < path.size(); i++)
    {
        if (edges[path[i - 1]][path[i]] < INT32_MAX)
        {
            vertices[path[i]]++;
            distance += edges[path[i - 1]][path[i]];
        }
        else
        {
            printf("Path %d: NA (Not a TS cycle)\n", path[0]);
            return;
        }
    }

    for (int i = 1; i <= vert_num; i++)
    {
        if (vertices[i] == 0)
        {
            printf("Path %d: %d (Not a TS cycle)\n", path[0], distance);
            return;
        }
    }

    if (distance < min_dist)
    {
        min_dist = distance;
        min_path = path[0];
    }

    if (path[1] == path[path.size() - 1])
    {
        if (path.size() == vert_num + 2)
        {
            printf("Path %d: %d (TS simple cycle)\n", path[0], distance);
        }
        else
        {
            printf("Path %d: %d (TS cycle)\n", path[0], distance);
        }
    }
    else
    {
        printf("Path %d: %d (Not a TS cycle)\n", path[0], distance);
    }
}

int main()
{
    for (int i = 0; i < MAX_VERT_NUM; i++)
    {
        edges[i][i] = INT32_MAX;
        for (int j = 0; j < i; j++)
        {
            edges[i][j] = INT32_MAX;
            edges[j][i] = INT32_MAX;
        }
    }

    cin >> vert_num >> edge_num;
    int source, target, distance;
    for (int i = 0; i < edge_num; i++)
    {
        cin >> source >> target >> distance;
        edges[source][target] = distance;
        edges[target][source] = distance;
    }

    vector<int> path;
    int query_num, path_len, vertex;

    cin >> query_num;
    for (int i = 0; i < query_num; i++)
    {
        cin >> path_len;
        path.push_back(i + 1);
        for (int j = 0; j < path_len; j++)
        {
            cin >> vertex;
            path.push_back(vertex);
        }
        follow_path(path);
        path.clear();
    }

    printf("Shortest Dist(%d) = %d\n", min_path, min_dist);
    return 0;
}