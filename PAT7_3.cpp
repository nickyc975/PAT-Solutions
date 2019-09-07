#include <iostream>
#include <unordered_set>

using namespace std;

int thresh, caller_num;
int suspected[1024] = {0};
int called[1024][1024] = {0};

int get_parent(int value)
{
    if (value != suspected[value])
    {
        return get_parent(suspected[value]);
    }
    return value;
}

void union_value(int a, int b)
{
    int a_p = get_parent(a);
    int b_p = get_parent(b);
    if (a_p != b_p)
    {
        suspected[a_p] = b_p;
    }
}

int main()
{
    int call_num, caller, recv, dur;
    cin >> thresh >> caller_num >> call_num;
    for (int i = 0; i < call_num; i++)
    {
        cin >> caller >> recv >> dur;
        called[caller][recv] += dur;
    }

    for (int i = 1; i <= caller_num; i++)
    {
        int short_cnt = 0, by_cnt = 0;
        for (int j = 1; j <= caller_num; j++)
        {
            if (called[i][j] > 0)
            {
                if (called[i][j] <= 5)
                {
                    short_cnt++;
                    if (called[j][i] > 0)
                    {
                        by_cnt++;
                    }
                }
            }
        }
        if (short_cnt > thresh && by_cnt * 5 <= short_cnt)
        {
            suspected[i] = i;
        }
    }

    for (int i = 1; i < caller_num; i++)
    {
        for (int j = i + 1; j <= caller_num; j++)
        {
            if (suspected[i] > 0 && suspected[j] > 0)
            {
                if (called[i][j] > 0 && called[j][i] > 0)
                {
                    union_value(i, j);
                }
            }
        }
    }

    bool flag = true;
    for (int i = 1; i <= caller_num; i++)
    {
        if (suspected[i] > 0)
        {
            cout << i;
            flag = false;
            int parent = get_parent(i);
            for (int j = i + 1; j <= caller_num; j++)
            {
                if (suspected[j] > 0 && get_parent(j) == parent)
                {
                    cout << " " << j;
                    suspected[j] = 0;
                }
            }
            cout << endl;
        }
    }

    if (flag)
    {
        cout << "None" << endl;
    }
    return 0;
}