#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    int row[1024] = {0}, diagonal[2048] = {0};
    int query_num, queen_num, value, prev_value;

    cin >> query_num;
    for (int i = 0; i < query_num; i++)
    {
        cin >> queen_num >> prev_value;

        bool flag = true;
        row[prev_value] = 1;
        diagonal[prev_value] = 1;
        for (int j = 1; j < queen_num; j++)
        {
            cin >> value;
            if (flag)
            {
                if (row[value] == 1 || diagonal[value + j] == 1)
                {
                    flag = false;
                }
                diagonal[value + j] = 1;
                row[value] = 1;
                prev_value = value;
            }
        }
        printf(flag ? "YES\n" : "NO\n");
        memset(row, 0, 1024 * sizeof(int));
        memset(diagonal, 0, 2048 * sizeof(int));
    }
    return 0;
}