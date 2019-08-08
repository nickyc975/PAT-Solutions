#include <stdio.h>
#include <stdlib.h>

typedef struct int_struct
{
    int value;
    struct int_struct *next;
} int_t;

int_t *new_int(int value);
int reverse(int value, int radix);
void print_int(int value, int radix);

int main()
{
    int value, radix;
    scanf("%d %d", &value, &radix);
    if (value == reverse(value, radix))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
    print_int(value, radix);
    return 0;
}

int_t *new_int(int value)
{
    int_t *int_v = (int_t *)malloc(sizeof(int_t));
    int_v->value = value;
    int_v->next = NULL;
    return int_v;
}

int reverse(int value, int radix)
{
    int reversed = 0;
    while (value > 0)
    {
        reversed = reversed * radix + value % radix;
        value /= radix;
    }
    return reversed;
}

void print_int(int value, int radix)
{
    int_t *head = NULL, *int_v;

    if (value == 0)
    {
        printf("0");
        return;
    }

    while (value > 0)
    {
        int_v = new_int(value % radix);
        int_v->next = head;
        head = int_v;
        value /= radix;
    }
    
    printf("%d", head->value);
    int_v = head;
    head = head->next;
    free(int_v);
    while (head != NULL)
    {
        printf(" %d", head->value);
        int_v = head;
        head = head->next;
        free(int_v);
    }
}