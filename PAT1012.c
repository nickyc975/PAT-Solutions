#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SCORE 101
#define STUDENT_NUM 2000

typedef enum
{
    A,
    C,
    M,
    E
} course_t;

typedef struct rank_struct
{
    int id;
    int score;
    struct rank_struct *next;
} rank_t;

typedef struct student_struct
{
    int id;
    int rank[4];
    struct student_struct *next;
} student_t;

char courses[] = {'A', 'C', 'M', 'E'};

rank_t *A_ranks[MAX_SCORE * 3 - 2];
rank_t *C_ranks[MAX_SCORE];
rank_t *M_ranks[MAX_SCORE];
rank_t *E_ranks[MAX_SCORE];
student_t *students[STUDENT_NUM];

rank_t *new_rank(int id, int score);
void put_rank(rank_t *ranks[], rank_t *rank, int max_score);
void cal_ranks(rank_t *ranks[], course_t course, int max_score);

student_t *new_student(int id);
void put_student(student_t *student);
student_t *get_student(int id);

int main()
{
    course_t course;
    student_t *student;
    int id, stu_num, query_num;
    int C_score, M_score, E_score, A_score;
    scanf("%d %d", &stu_num, &query_num);

    for (int i = 0; i < stu_num; i++)
    {
        scanf("%d %d %d %d", &id, &C_score, &M_score, &E_score);
        put_student(new_student(id));

        A_score = C_score + M_score + E_score;
        put_rank(A_ranks, new_rank(id, A_score), MAX_SCORE * 3 - 2);
        put_rank(C_ranks, new_rank(id, C_score), MAX_SCORE);
        put_rank(M_ranks, new_rank(id, M_score), MAX_SCORE);
        put_rank(E_ranks, new_rank(id, E_score), MAX_SCORE);
    }

    cal_ranks(A_ranks, A, MAX_SCORE * 3 - 2);
    cal_ranks(C_ranks, C, MAX_SCORE);
    cal_ranks(M_ranks, M, MAX_SCORE);
    cal_ranks(E_ranks, E, MAX_SCORE);

    for (int i = 0; i < query_num; i++)
    {
        scanf("%d", &id);
        student = get_student(id);

        if (student != NULL)
        {
            course = A;
            for (int j = A; j <= E; j++)
            {
                if (student->rank[j] < student->rank[course])
                {
                    course = (course_t)j;
                }
            }

            printf("%d %c\n", student->rank[course], courses[course]);
        }
        else
        {
            printf("N/A\n");
        }
    }

    return 0;
}

rank_t *new_rank(int id, int score)
{
    rank_t *rank = (rank_t *)malloc(sizeof(rank_t));
    memset(rank, 0, sizeof(rank_t));
    rank->id = id;
    rank->score = score;
    return rank;
}

void put_rank(rank_t *ranks[], rank_t *rank, int max_score)
{
    if (rank != NULL)
    {
        int index = rank->score % max_score;
        rank->next = ranks[index];
        ranks[index] = rank;
    }
}

void cal_ranks(rank_t *ranks[], course_t course, int max_score)
{
    rank_t *rank;
    student_t *student;
    int count = 1, same_score;
    for (int i = max_score; i > 0; i--)
    {
        same_score = 0;
        rank = ranks[i - 1];
        while (rank != NULL)
        {
            student = get_student(rank->id);
            student->rank[course] = count;
            rank = rank->next;
            same_score++;
        }
        count += same_score;
    }
}

student_t *new_student(int id)
{
    student_t *student = (student_t *)malloc(sizeof(student_t));
    memset(student, 0, sizeof(student_t));
    student->id = id;
    return student;
}

void put_student(student_t *student)
{
    if (student != NULL)
    {
        int index = student->id % STUDENT_NUM;
        student->next = students[index];
        students[index] = student;
    }
}

student_t *get_student(int id)
{
    int index = id % STUDENT_NUM;
    student_t *student = students[index];
    while (student != NULL && student->id != id)
    {
        student = student->next;
    }
    return student;
}

/*
5 6
310101 98 85 88
310102 70 95 88
310103 82 87 94
310104 91 91 91
310105 85 90 90
310101
310102
310103
310104
310105
999999
 */