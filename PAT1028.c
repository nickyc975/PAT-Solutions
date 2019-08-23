#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student_struct
{
    int id, score;
    char name[10];
} student_t;

int stu_num;
student_t students[100000];

int cmp_id(const void *a, const void *b)
{
    return ((student_t *)a)->id - ((student_t *)b)->id;
}

int cmp_name(const void *a, const void *b)
{
    int result = strcmp(((student_t *)a)->name, ((student_t *)b)->name);
    if (result == 0)
    {
        result = cmp_id(a, b);
    }
    return result;
}

int cmp_score(const void *a, const void *b)
{
    int result = ((student_t *)a)->score - ((student_t *)b)->score;
    if (result == 0)
    {
        result = cmp_id(a, b);
    }
    return result;
}

int main()
{
    char ch;
    int sort, length;
    scanf("%d %d", &stu_num, &sort);
    for (int i = 0; i < stu_num; i++)
    {
        scanf("%d ", &(students[i].id));
        length = 0;
        ch = getchar();
        while (ch != ' ')
        {
            students[i].name[length] = ch;
            ch = getchar();
            length++;
        }
        students[i].name[length] = 0;
        scanf("%d", &(students[i].score));
    }

    switch (sort)
    {
        case 1:
            qsort(students, stu_num, sizeof(student_t), cmp_id);
            break;
        case 2:
            qsort(students, stu_num, sizeof(student_t), cmp_name);
            break;
        case 3:
            qsort(students, stu_num, sizeof(student_t), cmp_score);
            break;
        default:
            break;
    }

    for (int i = 0; i < stu_num; i++)
    {
        printf("%06d %s %d\n", students[i].id, students[i].name, students[i].score);
    }
    return 0;
}