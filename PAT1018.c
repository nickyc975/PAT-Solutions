#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x6FFFFFFF
#define MAX_VERTICES_NUM 501

typedef struct node_struct
{
    int vertex;
    struct node_struct *next;
} node_t;

typedef struct list_struct
{
    node_t *node;
    struct list_struct *next;
} list_t;

int half;
int vertices_num, edges_num;
int vertices[MAX_VERTICES_NUM];
int edges[MAX_VERTICES_NUM][MAX_VERTICES_NUM];
node_t *paths[MAX_VERTICES_NUM];

node_t *new_node(int vertex);
list_t *new_list(node_t *node);
void free_node(node_t *node);
void dijkstra();
int get_next(int found[], int distances[]);
list_t *extract_path(int target);

int main()
{
    int target;
    scanf("%d %d %d %d", &half, &vertices_num, &target, &edges_num);
    half /= 2;
    for (int i = 1; i <= vertices_num; i++)
    {
        scanf("%d", &vertices[i]);
        vertices[i] -= half;
    }

    for (int i = 0; i <= vertices_num; i++)
    {
        for (int j = 0; j <= vertices_num; j++)
        {
            if (i == j)
            {
                edges[i][j] = 0;
                edges[j][i] = 0;
            }
            else
            {
                edges[i][j] = INF;
                edges[j][i] = INF;
            }
        }
    }

    int s, t, c;
    for (int i = 0; i < edges_num; i++)
    {
        scanf("%d %d %d", &s, &t, &c);
        edges[s][t] = c;
        edges[t][s] = c;
    }

    dijkstra();

    int need, min_need = INF;
    int back, min_back = INF;
    node_t *node_cursor, *min_path;
    list_t *result = extract_path(target), *list_cursor = result;
    while (list_cursor != NULL)
    {
        need = 0, back = 0;
        node_cursor = list_cursor->node;
        while (node_cursor->next != NULL)
        {
            node_cursor = node_cursor->next;
            back += vertices[node_cursor->vertex];
            if (back < 0)
            {
                need += -back;
                back = 0;
            }
        }

        if (need < min_need || (need == min_need && back < min_back))
        {
            min_need = need;
            min_back = back;
            min_path = list_cursor->node;
        }

        list_cursor = list_cursor->next;
    }

    printf("%d %d", min_need, min_path->vertex);
    while (min_path->next != NULL)
    {
        min_path = min_path->next;
        printf("->%d", min_path->vertex);
    }
    printf(" %d", min_back);

    return 0;
}

node_t *new_node(int vertex)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->vertex = vertex;
    node->next = NULL;
    return node;
}

list_t *new_list(node_t *node)
{
    list_t *list = (list_t *)malloc(sizeof(list_t));
    list->node = node;
    list->next = NULL;
    return list;
}

void free_node(node_t *node)
{
    if (node != NULL)
    {
        free_node(node->next);
        free(node);
    }
}

void dijkstra()
{
    int found[MAX_VERTICES_NUM];
    int distances[MAX_VERTICES_NUM];
    found[0] = 1, distances[0] = 0;
    for (int i = 1; i <= vertices_num; i++)
    {
        found[i] = 0;
        distances[i] = edges[0][i];
        if (distances[i] < INF)
        {
            paths[i] = new_node(0);
        }
        else
        {
            paths[i] = NULL;
        }
    }

    node_t *node;
    int next = get_next(found, distances);
    while (next != 0 && distances[next] < INF)
    {
        found[next] = 1;
        for (int i = 1; i <= vertices_num; i++)
        {
            int new_distance = distances[next] + edges[next][i];
            if (new_distance < distances[i])
            {
                distances[i] = new_distance;
                free_node(paths[i]);
                paths[i] = new_node(next);
            }
            else if (new_distance == distances[i] && next != i && new_distance < INF)
            {
                node = new_node(next);
                node->next = paths[i];
                paths[i] = node;
            }
        }

        next = get_next(found, distances);
    }
}

int get_next(int found[], int distances[])
{
    int next = 0;
    for (int i = 1; i <= vertices_num; i++)
    {
        if (found[i] == 0)
        {
            if (found[next] != 0 || distances[i] < distances[next])
            {
                next = i;
            }
        }
    }
    return next;
}

list_t *extract_path(int target)
{
    node_t *prev = paths[target];
    list_t *list = NULL, *head, *tail;
    while (prev != NULL)
    {
        if (prev->vertex == 0)
        {
            head = new_list(new_node(prev->vertex));
            head->next = list;
            list = head;
        }
        else
        {
            head = extract_path(prev->vertex);
            if (head != NULL)
            {
                tail = head;
                while (tail->next != NULL)
                {
                    tail = tail->next;
                }
                tail->next = list;
                list = head;
            }
        }
        prev = prev->next;
    }

    head = list;
    while (head != NULL)
    {
        prev = head->node;
        while (prev->next != NULL)
        {
            prev = prev->next;
        }
        prev->next = new_node(target);
        head = head->next;
    }
    
    return list;
}