#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_FACTOR 1009
#define CUSTOMER_NUM 1000

typedef struct record_struct
{
    int time, is_on;
    struct record_struct *next;
} record_t;

typedef struct customer_struct
{
    int name_len;
    char name[24];
    record_t *records;
    struct customer_struct *next;
} customer_t;

int toll[24], month;
int customer_num = 0;
customer_t *hashed_customers[HASH_FACTOR];
customer_t *sorted_customers[CUSTOMER_NUM];

int get_date(int time);
int get_hour(int time);
int get_minute(int time);
float get_bill(int on, int off);
int hash(char str[], int length);
record_t *new_record(int time, int is_on);
customer_t *new_customer(char name[], int name_len);
void put_customer(customer_t *customer);
customer_t *get_customer(char name[], int name_len);
void append_customer(customer_t *customer);
void append_record(customer_t *customer, record_t *record);
void print_bill(customer_t *customer);

int cmp_customer(const void *a, const void *b)
{
    customer_t *c_a = *((customer_t **)a);
    customer_t *c_b = *((customer_t **)b);
    int length = c_a->name_len < c_b->name_len ? c_a->name_len : c_b->name_len;
    for (int i = 0; i < length; i++)
    {
        if (c_a->name[i] != c_b->name[i])
        {
            return c_a->name[i] - c_b->name[i];
        }
    }

    return c_a->name_len - c_b->name_len;
}

int main()
{
    customer_t *customer;
    record_t *record;
    char name[24], ch, on_off[10];
    int record_num, name_len;
    int date, hour, minute;

    for (int i = 0; i < 24; i++)
    {
        scanf("%d", &toll[i]);
    }

    scanf("%d", &record_num);
    for (int i = 0; i < record_num; i++)
    {
        name_len = 0;
        ch = getchar();
        while (ch == '\n')
        {
            ch = getchar();
        }

        while (ch != ' ')
        {
            name[name_len] = ch;
            ch = getchar();
            name_len++;
        }
        name[name_len] = 0;
        scanf("%d:%d:%d:%d %s", &month, &date, &hour, &minute, on_off);
        customer = get_customer(name, name_len);
        if (customer == NULL)
        {
            customer = new_customer(name, name_len);
            append_customer(customer);
            put_customer(customer);
        }
        append_record(customer, new_record(date * 24 * 60 + hour * 60 + minute, on_off[1] == 'n'));
    }

    qsort(sorted_customers, customer_num, sizeof(customer_t *), cmp_customer);

    for (int i = 0; i < customer_num; i++)
    {
        print_bill(sorted_customers[i]);
    }

    return 0;
}

int get_date(int time)
{
    return time / (24 * 60);
}

int get_hour(int time)
{
    return (time % (24 * 60)) / 60;
}

int get_minute(int time)
{
    return time % 60;
}

float get_bill(int on, int off)
{
    int on_hour = get_hour(on), on_minute = get_minute(on);
    int off_hour = get_hour(off), off_minute = get_minute(off);

    float cents = 0.0;
    cents += toll[on_hour] * (60 - on_minute);
    off_hour += (get_date(off) - get_date(on)) * 24;
    on_hour++;
    while (on_hour < off_hour)
    {
        cents += toll[on_hour % 24] * 60;
        on_hour++;
    }
    cents += toll[on_hour % 24] * off_minute;
    return cents / 100;
}

int hash(char str[], int length)
{
    int value = 0;
    for (int i = 0; i < length; i++)
    {
        value += str[i];
    }
    return value % HASH_FACTOR;
}

record_t *new_record(int time, int is_on)
{
    record_t *record = (record_t *)malloc(sizeof(record_t));
    record->time = time;
    record->is_on = is_on;
    record->next = NULL;
    return record;
}

customer_t *new_customer(char name[], int name_len)
{
    customer_t *customer = (customer_t *)malloc(sizeof(customer_t));
    strncpy(customer->name, name, name_len);
    customer->name_len = name_len;
    customer->name[name_len] = 0;
    customer->records = NULL;
    customer->next = NULL;
    return customer;
}

void put_customer(customer_t *customer)
{
    int index = hash(customer->name, customer->name_len);
    customer->next = hashed_customers[index];
    hashed_customers[index] = customer;
}

customer_t *get_customer(char name[], int name_len)
{
    int index = hash(name, name_len);
    customer_t *customer = hashed_customers[index];
    while (customer != NULL && strcmp(name, customer->name) != 0)
    {
        customer = customer->next;
    }
    return customer;
}

void append_customer(customer_t *customer)
{
    sorted_customers[customer_num] = customer;
    customer_num++;
}

void append_record(customer_t *customer, record_t *record)
{
    record_t **record_ptr = &(customer->records);
    while (*record_ptr != NULL && (*record_ptr)->time < record->time)
    {
        record_ptr = &((*record_ptr)->next);
    }
    record->next = *record_ptr;
    *record_ptr = record;
}

void print_bill(customer_t *customer)
{
    int has_bill = 0;
    float bill, total = 0.0;
    int prev_time, prev_is_on = 0;
    record_t *record = customer->records;
    while (record != NULL)
    {
        if (prev_is_on && !record->is_on)
        {
            has_bill = 1;
            break;
        }
        prev_is_on = record->is_on;
        record = record->next;
    }

    if (has_bill)
    {
        prev_is_on = 0;
        record = customer->records;
        printf("%s %02d\n", customer->name, month);
        while (record != NULL)
        {
            if (prev_is_on && !record->is_on)
            {
                bill = get_bill(prev_time, record->time);
                total += bill;
                printf(
                    "%02d:%02d:%02d %02d:%02d:%02d %d $%.2f\n", 
                    get_date(prev_time), get_hour(prev_time), get_minute(prev_time), 
                    get_date(record->time), get_hour(record->time), get_minute(record->time), 
                    record->time - prev_time, bill
                );
            }

            prev_time = record->time;
            prev_is_on = record->is_on;
            record = record->next;
        }
        printf("Total amount: $%.2f\n", total);
    }
}
