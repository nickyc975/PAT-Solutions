#include <stdio.h>
#include <stdlib.h>

typedef enum {
    A, C, M, E
} course_t;

typedef struct rank_struct
{
    int id;
    double score;
    struct rank_struct *next;
} rank_t;

typedef struct student_struct
{
    int id;
    int rank[4];
    struct student_struct *next;
} student_t;

rank_t *A_ranks[101];
rank_t *C_ranks[101];
rank_t *M_ranks[101];
rank_t *E_ranks[101];
student_t *students[2000];

void put(student_t *student);
student_t *get(int id);

int main()
{
    return 0;
}

void put(student_t *student)
{

}

student_t *get(int id)
{

}