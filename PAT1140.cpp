#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int d, n;
    cin >> d >> n;
    vector<char> numbers[2];
    numbers[0].push_back(d + '0');
    for (int i = 1; i < n; i++)
    {
        int cnt = 1;
        numbers[i % 2].push_back(numbers[(i - 1) % 2][0]);
        for (int j = 1; j < numbers[(i - 1) % 2].size(); j++)
        {
            if (numbers[(i - 1) % 2][j] == numbers[(i - 1) % 2][j - 1])
            {
                cnt++;
            }
            else
            {
                numbers[i % 2].push_back(cnt + '0');
                numbers[i % 2].push_back(numbers[(i - 1) % 2][j]);
                cnt = 1;
            }
        }
        numbers[i % 2].push_back(cnt + '0');
        numbers[(i - 1) % 2].clear();
    }
    for (int i = 0; i < numbers[(n - 1) % 2].size(); i++)
    {
        printf("%c", numbers[(n - 1) % 2][i]);
    }
    return 0;
}