#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int numbers[400];

int cmp(const void *a, const void *b)
{
    return *((int *)b) - *((int *)a);
}

int fast_pow(int value, int exp)
{
    int remain = 1;
    while (exp > 1)
    {
        if (exp % 2 != 0)
        {
            remain *= value;
        }

        value *= value;
        exp /= 2;
    }
    return value * remain;
}

int factorization(int N, int K, int P)
{
    if (N < K || K == 0)
    {
        return 0;
    }

    if (K == 1)
    {
        for (int i = 1; i < (int)sqrt(N) + 1; i++)
        {
            if (fast_pow(i, P) == N)
            {
                numbers[K - 1] = i;
                return 1;
            }
        }
        return 0;
    }

    int low = N / K, high = low + 1;
    while (low > 0 || high <= N)
    {
        if (low > 0)
        {
            for (int i = 1; i < (int)sqrt(low) + 1; i++)
            {
                if (fast_pow(i, P) == low && factorization(N - low, K - 1, P))
                {
                    numbers[K - 1] = i;
                    return 1;
                }
            }
            low--;
        }

        if (high <= N)
        {
            for (int i = 1; i < (int)sqrt(high) + 1; i++)
            {
                if (fast_pow(i, P) == high && factorization(N - high, K - 1, P))
                {
                    numbers[K - 1] = i;
                    return 1;
                }
            }
            high++;
        }
    }
    return 0;
}

int main()
{
    int N, K, P;
    scanf("%d %d %d", &N, &K, &P);
    if (factorization(N, K, P))
    {
        qsort(numbers, K, sizeof(int), cmp);
        printf("%d = %d^%d", N, numbers[0], P);
        for (int i = 1; i < K; i++)
        {
            printf(" + %d^%d", numbers[i], P);
        }
    }
    else
    {
        printf("Impossible");
    }
    printf("\n");
    return 0;
}