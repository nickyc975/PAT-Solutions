#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES_NUM 10000

typedef struct node_struct
{
    int vertex;
    struct node_struct *next;
} node_t;

int visited[MAX_VERTICES_NUM];
node_t *vertices[MAX_VERTICES_NUM];
int visited_num, vertices_num, max_depth = 0;

node_t *new_node(int vertex);
void free_nodes(node_t *node);
void print_nodes(node_t *node);
int dfs(int source);
int get_components_num();

int main()
{
    int source, target, depth;
    node_t *head = NULL, *node;
    scanf("%d", &vertices_num);
    for (int i = 0; i < vertices_num; i++)
    {
        vertices[i] = NULL;
    }

    for (int i = 1; i < vertices_num; i++)
    {
        scanf("%d %d", &source, &target);
        source--, target--;

        node = new_node(target);
        node->next = vertices[source];
        vertices[source] = node;

        node = new_node(source);
        node->next = vertices[target];
        vertices[target] = node;
    }

    for (int i = 0; i < vertices_num; i++)
    {
        visited_num = 1;
        memset(visited, 0, sizeof(int) * vertices_num);
        visited[i] = 1;
        depth = dfs(i);

        if (visited_num < vertices_num)
        {
            visited_num = 0;
            memset(visited, 0, sizeof(int) * vertices_num);
            printf("Error: %d components", get_components_num());
            return 0;
        }
        else if (depth > max_depth)
        {
            free_nodes(head);
            head = new_node(i);
            max_depth = depth;
        }
        else if (depth == max_depth)
        {
            node = new_node(i);
            node->next = head;
            head = node;
        }
    }

    print_nodes(head);

    return 0;
}

node_t *new_node(int vertex)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->vertex = vertex;
    node->next = NULL;
    return node;
}

void free_nodes(node_t *node)
{
    if (node != NULL)
    {
        free_nodes(node->next);
        free(node);
    }
}

void print_nodes(node_t *node)
{
    if (node != NULL)
    {
        print_nodes(node->next);
        printf("%d\n", node->vertex + 1);
    }
}

int dfs(int source)
{
    int depth = 0, temp;
    node_t *node = vertices[source];
    while (node != NULL)
    {
        if (visited[node->vertex] == 0)
        {
            visited[node->vertex] = 1;
            visited_num++;

            temp = dfs(node->vertex);
            depth = temp > depth ? temp : depth;
        }
        node = node->next;
    }
    return depth + 1;
}

int get_components_num()
{
    int components_num = 0;
    while (visited_num < vertices_num)
    {
        int source = 0;
        while (source < vertices_num && visited[source] != 0)
        {
            source++;
        }
        
        if (source < vertices_num)
        {
            visited[source] = 1;
            visited_num++;
            dfs(source);
        }

        components_num++;
    }
    return components_num;
}