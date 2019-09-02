#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N, a;
    cin >> N;
    vector<int> numbers(N + 1, 0);
    for (int i = 0; i < N; i++)
    {
        cin >> a;
        if (a > 0 && a <= N)
        {
            numbers[a] = 1;
        }
    }
    for (int i = 1; i <= N; i++)
    {
        if (numbers[i] == 0)
        {
            printf("%d", i);
            return 0;
        }
    }
    printf("%d", N + 1);
    return 0;
}