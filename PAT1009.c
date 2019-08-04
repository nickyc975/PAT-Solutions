#include <stdio.h>
#include <stdlib.h>

typedef struct node_struct
{
    int exp;
    double coe;
    struct node_struct *next;
} node_t;

node_t *new_node(int exp, double coe);
void free_node(node_t *node);

int main()
{
    int exp, exp_prod;
    double coe, coe_prod;
    int a_num, b_num, prod_num = 0;
    node_t *a_head = NULL, *prod_head = NULL, *temp = NULL;
    node_t **a_cursor = &a_head, **prod_cursor = &prod_head;
    
    int i;
    scanf("%d", &a_num);
    for (i = 0; i < a_num; i++)
    {
        scanf("%d %lf", &exp, &coe);
        *a_cursor = new_node(exp, coe);
        a_cursor = &((*a_cursor)->next);
    }

    a_cursor = &a_head;

    scanf("%d", &b_num);
    for (i = 0; i < b_num; i++)
    {
        scanf("%d %lf", &exp, &coe);
        while (*a_cursor != NULL)
        {
            exp_prod = exp + (*a_cursor)->exp;
            coe_prod = coe * (*a_cursor)->coe;
            while (*prod_cursor != NULL && (*prod_cursor)->exp > exp_prod)
            {
                prod_cursor = &((*prod_cursor)->next);
            }
            
            if (*prod_cursor == NULL)
            {
                *prod_cursor = new_node(exp_prod, coe_prod);
                prod_num++;
            }
            else if ((*prod_cursor)->exp < exp_prod)
            {
                temp = new_node(exp_prod, coe_prod);
                temp->next = *prod_cursor;
                *prod_cursor = temp;
                prod_num++;
            }
            else
            {
                (*prod_cursor)->coe += coe_prod;
                if ((*prod_cursor)->coe == 0)
                {
                    temp = *prod_cursor;
                    *prod_cursor = (*prod_cursor)->next;
                    prod_num--;
                    free(temp);
                }
            }
            prod_cursor = &prod_head;
            a_cursor = &((*a_cursor)->next);
        }
        a_cursor = &a_head;
    }

    printf("%d", prod_num);
    while (*prod_cursor != NULL)
    {
        printf(" %d %.1lf", (*prod_cursor)->exp, (*prod_cursor)->coe);
        prod_cursor = &((*prod_cursor)->next);
    }
    

    free_node(prod_head);
    free_node(a_head);
    return 0;
}

node_t *new_node(int exp, double coe)
{
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->exp = exp;
    node->coe = coe;
    node->next = NULL;
    return node;
}

void free_node(node_t *node)
{
    if (node != NULL)
    {
        free_node(node->next);
        free(node);
    }
}