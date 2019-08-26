#include <stdio.h>
#include <stdlib.h>
#define PRIME 1009
#define MAX_NUM 10000

typedef struct edge_struct
{
    int source;
    int target;
} edge_t;

typedef struct node_struct
{
    int value;
    struct node_struct *next;
} node_t;

typedef struct set_struct
{
    int size;
    node_t *nodes[PRIME];
} set_t;

int vertices[MAX_NUM];
edge_t edges[MAX_NUM];
int vertex_num, edge_num;

set_t *new_set()
{
    set_t *set = (set_t *)malloc(sizeof(set_t));
    set->size = 0;
    for (int i = 0; i < PRIME; i++)
    {
        set->nodes[i] = NULL;
    }
    return set;
}

node_t *new_node(int value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->value = value;
    node->next = NULL;
    return node;
}

int put(set_t *set, int value)
{
    int hash = value % PRIME;
    node_t **node_ptr = &(set->nodes[hash]);
    while (*node_ptr != NULL)
    {
        if ((*node_ptr)->value == value)
        {
            return 0;
        }
        node_ptr = &((*node_ptr)->next);
    }
    
    *node_ptr = new_node(value);
    set->size++;
    return 1;
}

void clear(set_t *set)
{
    node_t *node;
    for (int i = 0; i < PRIME; i++)
    {
        while (set->nodes[i] != NULL)
        {
            node = set->nodes[i];
            set->nodes[i] = set->nodes[i]->next;
            free(node);
        }
    }
    set->size = 0;
}

int main()
{
    set_t *set = new_set();
    int query_num, is_coloring;
    scanf("%d %d", &vertex_num, &edge_num);
    for (int i = 0; i < edge_num; i++)
    {
        scanf("%d %d", &(edges[i].source), &(edges[i].target));
    }
    scanf("%d", &query_num);
    while (query_num > 0)
    {
        is_coloring = 1;
        for (int i = 0; i < vertex_num; i++)
        {
            scanf("%d", &(vertices[i]));
        }

        for (int i = 0; i < edge_num; i++)
        {
            if (vertices[edges[i].source] == vertices[edges[i].target])
            {
                is_coloring = 0;
                break;
            }
        }

        if (is_coloring)
        {
            for (int i = 0; i < vertex_num; i++)
            {
                put(set, vertices[i]);
            }
            printf("%d-coloring\n", set->size);
            clear(set);
        }
        else
        {
            printf("No\n");
        }

        query_num--;
    }
    
    free(set);
    return 0;
}