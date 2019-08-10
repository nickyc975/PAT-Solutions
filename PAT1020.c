#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE_NUM 30

typedef struct node_struct
{
    int value;
    struct node_struct *parent;
    struct node_struct *left_child;
    struct node_struct *right_child;
} node_t;

typedef struct list_node_struct
{
    node_t *value;
    struct list_node_struct *next;
} list_node_t;

int node_num;
int in_seq[MAX_NODE_NUM];
int post_seq[MAX_NODE_NUM];

node_t *new_node(int value, node_t *parent);
list_node_t *new_list_node(node_t *value);
int index_of(int value, int array[], int array_len);
void level_order(node_t *root);

int main()
{
    scanf("%d", &node_num);
    for (int i = 0; i < node_num; i++)
    {
        scanf("%d", &post_seq[i]);
    }
    for (int i = 0; i < node_num; i++)
    {
        scanf("%d", &in_seq[i]);
    }

    int index, prev_index;
    node_t *root, *prev, *node;
    root = new_node(post_seq[node_num - 1], NULL);
    prev = root;
    for (int i = node_num - 2; i >= 0; i--)
    {
        node = new_node(post_seq[i], NULL);
        index = index_of(post_seq[i], in_seq, node_num);
        prev_index = index_of(prev->value, in_seq, node_num);

        if (index > prev_index)
        {
            node->parent = prev;
            prev->right_child = node;
        }
        else
        {
            while (prev->parent != NULL)
            {
                prev_index = index_of(prev->parent->value, in_seq, node_num);
                if (index > prev_index)
                {
                    break;
                }
                prev = prev->parent;
            }

            while (prev->left_child != NULL)
            {
                prev = prev->left_child;
            }

            node->parent = prev;
            prev->left_child = node;
        }

        prev = node;
    }

    level_order(root);

    return 0;
}

node_t *new_node(int value, node_t *parent)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->value = value;
    node->parent = parent;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}

list_node_t *new_list_node(node_t *value)
{
    list_node_t *node = (list_node_t *)malloc(sizeof(list_node_t));
    node->value = value;
    node->next = NULL;
    return node;
}

int index_of(int value, int array[], int array_len)
{
    for (int i = 0; i < array_len; i++)
    {
        if (array[i] == value)
        {
            return i;
        }
    }
    
    return -1;
}

void level_order(node_t *root)
{
    list_node_t *head, **tail = &head;
    printf("%d", root->value);
    if (root->left_child != NULL)
    {
        *tail = new_list_node(root->left_child);
        tail = &((*tail)->next);
    }

    if (root->right_child != NULL)
    {
        *tail = new_list_node(root->right_child);
        tail = &((*tail)->next);
    }

    while (head != NULL)
    {
        if (head->value->left_child != NULL)
        {
            *tail = new_list_node(head->value->left_child);
            tail = &((*tail)->next);
        }

        if (head->value->right_child != NULL)
        {
            *tail = new_list_node(head->value->right_child);
            tail = &((*tail)->next);
        }

        printf(" %d", head->value->value);
        head = head->next;
    }
}
