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
int testee_num = 0, ranks[101];

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

    memset(ranks, 0, 101 * sizeof(int));
    memset(testees, 0, 101 * sizeof(testee_t *));

    scanf("%d", &loc_num);
    for (int i = 0; i < loc_num; i++)
    {
        scanf("%d", &loc_testee_num);
        testee_num += loc_testee_num;
        while (loc_testee_num > 0)
        {
            testee = new_testee(i + 1);
            scanf("%llu %d", &(testee->reg_num), &(testee->score));
            insert(&(testees[testee->score]), testee);
            loc_testee_num--;
        }
    }

    printf("%d\n", testee_num);

    int count[101];
    memset(count, 0, 101 * sizeof(int));
    for (int i = 100; i >= 0; i--)
    {
        testee = testees[i];
        while (testee != NULL)
        {
            count[0]++;
            count[testee->loc]++;
            printf("%013llu %d %d %d\n", testee->reg_num, ranks[0] + 1, testee->loc, ranks[testee->loc] + 1);
            testee = testee->next;
        }

        for (int j = 0; j < loc_num + 1; j++)
        {
            ranks[j] += count[j];
            count[j] = 0;
        }
    }
    
    return 0;
}