#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct testee_struct
{
    int loc, score;
    unsigned long long reg_num;
    struct testee_struct *next;
} testee_t;

testee_t *testees[101];
int testee_num = 0, rank = 0, loc_ranks[100];

testee_t *new_testee(int loc)
{
    testee_t *testee = (testee_t *)malloc(sizeof(testee_t));
    testee->loc = loc;
    testee->score = 0;
    testee->reg_num = 0;
    testee->next = NULL;
    return testee;
}

void insert(testee_t **head, testee_t *testee)
{
    while (*head != NULL && (*head)->reg_num < testee->reg_num)
    {
        head = &((*head)->next);
    }
    testee->next = *head;
    *head = testee;
}

int main()
{
    int loc_num, loc_testee_num;
    testee_t *head = NULL, *testee;

    memset(testees, 0, 101 * sizeof(testee_t *));
    memset(loc_ranks, 0, 100 * sizeof(int));

    scanf("%d", &loc_num);
    for (int i = 0; i < loc_num; i++)
    {
        scanf("%d", &loc_testee_num);
        testee_num += loc_testee_num;
        while (loc_testee_num > 0)
        {
            testee = new_testee(i);
            scanf("%llu %d", &(testee->reg_num), &(testee->score));
            insert(&(testees[testee->score]), testee);
            loc_testee_num--;
        }
    }

    int count, loc_count[100];
    for (int i = 100; i >= 0; i--)
    {
        testee = testees[i];

        count = 0;
        memset(loc_count, 0, sizeof(int));
        while (testee != NULL)
        {
            
        }
    }
    
    return 0;
}