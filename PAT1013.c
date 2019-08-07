#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERTICES_NUM 1000

int vertices[VERTICES_NUM];
int edges[VERTICES_NUM][VERTICES_NUM];
int vertices_num, edges_num;

int get_cc_num();
int get_source();
void dfs();
void remove_v(int vertex);
void resave_v(int vertex);

int main()
{
    int query_num, source, target;
    scanf("%d %d %d", &vertices_num, &edges_num, &query_num);

    for (int i = 0; i < vertices_num; i++)
    {
        memset(edges[i], 0, sizeof(int) * vertices_num);
    }

    for (int i = 0; i < edges_num; i++)
    {
        scanf("%d %d", &source, &target);
        edges[source - 1][target - 1] = 1;
        edges[target - 1][source - 1] = 1;
    }

    for(int i = 0; i < query_num; i++)
    {
        scanf("%d", &source);
        memset(vertices, 0, sizeof(int) * vertices_num);

        remove_v(source - 1);
        printf("%d\n", get_cc_num() - 1);
        resave_v(source - 1);
    }
    return 0;
}

int get_cc_num()
{
    int count = 0;
    int source = get_source();
    while (source >= 0)
    {
        vertices[source] = 1;
        dfs(source);

        source = get_source();
        count++;
    }
    return count;
}

int get_source()
{
    for (int i = 0; i < vertices_num; i++)
    {
        if (vertices[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

void dfs(int source)
{
    for (int i = 0; i < vertices_num; i++)
    {
        if (edges[source][i] > 0 && vertices[i] == 0)
        {
            vertices[i] = 1;
            dfs(i);
        }
    }
}

void remove_v(int vertex)
{
    for (int i = 0; i < vertices_num; i++)
    {
        if (edges[vertex][i] > 0)
        {
            edges[vertex][i] = -1;
        }
        
        if (edges[i][vertex] > 0)
        {
            edges[i][vertex] = -1;
        }
    }
    vertices[vertex] = 1;
}

void resave_v(int vertex)
{
    for (int i = 0; i < vertices_num; i++)
    {
        if (edges[vertex][i] < 0)
        {
            edges[vertex][i] = 1;
        }

        if (edges[i][vertex] < 0)
        {
            edges[i][vertex] = 1;
        }
    }
    vertices[vertex] = 0;
}