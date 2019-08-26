#include <stdio.h>
#include <stdlib.h>

typedef struct node_struct
{
    int value;
    struct node_struct *lchild;
    struct node_struct *rchild;
} node_t;

typedef struct queue_node_struct
{
    node_t *value;
    struct queue_node_struct *next;
} queue_node_t;

typedef struct queue_struct
{
    queue_node_t *head;
    queue_node_t *rear;
} queue_t;

int is_heap = 1, order = 0;
int stack[100], stk_cursor = 0;

node_t *new_node(int value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->value = value;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

queue_node_t *new_queue_node(node_t *value)
{
    queue_node_t *node = (queue_node_t *)malloc(sizeof(queue_node_t));
    node->value = value;
    node->next = NULL;
    return node;
}

queue_t *new_queue()
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    queue->head = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(queue_t *queue, node_t *value)
{
    queue_node_t *node = new_queue_node(value);
    if (queue->head == NULL)
    {
        queue->head = node;
        queue->rear = node;
    }
    else
    {
        queue->rear->next = node;
        queue->rear = node;
    }
}

node_t *dequeue(queue_t *queue)
{
    node_t *value = NULL;
    queue_node_t *removed;
    if (queue->head != NULL)
    {
        removed = queue->head;
        queue->head = queue->head->next;
        if (queue->head == NULL)
        {
            queue->rear = NULL;
        }
        value = removed->value;
        free(removed);
    }
    return value;
}

node_t *head(queue_t *queue)
{
    node_t *value = NULL;
    if (queue->head != NULL)
    {
        value = queue->head->value;
    }
    return value;
}

int not_empty(queue_t *queue)
{
    return queue->head != NULL;
}

void check_order(int parent, int child)
{
    int diff = parent - child;
    if (diff != 0 && is_heap != 0)
    {
        if (order == 0)
        {
            order = diff > 0 ? 1 : -1;
        }
        else if ((order > 0 && diff < 0) || (order < 0 && diff > 0))
        {
            is_heap = 0;
        }
    }
}

void tranverse(node_t *root)
{
    int haschild = 0;
    stack[stk_cursor++] = root->value;
    if (root->rchild != NULL)
    {
        check_order(root->value, root->rchild->value);
        tranverse(root->rchild);
        haschild = 1;
    }
    
    if (root->lchild != NULL)
    {
        check_order(root->value, root->lchild->value);
        tranverse(root->lchild);
        haschild = 1;
    }

    if (!haschild)
    {
        printf("%d", stack[0]);
        for (int i = 1; i < stk_cursor; i++)
        {
            printf(" %d", stack[i]);
        }
        printf("\n");
    }
    stk_cursor--;
}

int main()
{
    int node_num, value;
    node_t *root, *node;
    queue_t *queue = new_queue();
    scanf("%d\n%d", &node_num, &value);
    root = new_node(value);
    enqueue(queue, root);
    for (int i = 1; i < node_num; i++)
    {
        scanf(" %d", &value);
        node = new_node(value);
        if (i % 2 == 1)
        {
            head(queue)->lchild = node;
        }
        else
        {
            dequeue(queue)->rchild = node;
        }
        enqueue(queue, node);
    }

    while (not_empty(queue))
    {
        dequeue(queue);
    }
    
    tranverse(root);

    if (is_heap)
    {
        if (order > 0)
        {
            printf("Max Heap\n");
        }
        else
        {
            printf("Min Heap\n");
        }
    }
    else
    {
        printf("Not Heap\n");
    }

    return 0;
}