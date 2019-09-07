#include <iostream>
#include <set>

using namespace std;

int values[100000] = {0};
bool flags[100000] = {false};

int main()
{
    int value_num;
    int prev_max = 0, post_min = 0x7FFFFFFF;

    cin >> value_num;
    for (int i = 0; i < value_num; i++)
    {
        cin >> values[i];
        if (values[i] > prev_max)
        {
            prev_max = values[i];
            flags[i] = true;
        }
    }

    set<int> pivots;
    for (int i = value_num - 1; i >= 0; i--)
    {
        if (values[i] < post_min)
        {
            post_min = values[i];
            if (flags[i])
            {
                pivots.insert(values[i]);
            }
        }
    }

    int count = 0;
    cout << pivots.size() << endl;
    for (int pivot : pivots)
    {
        if (count == 0)
        {
            cout << pivot;
        }
        else
        {
            cout << " " << pivot;
        }
        count++;
    }
    cout << endl;
    return 0;
}