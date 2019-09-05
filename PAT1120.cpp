#include <iostream>
#include <set>

using namespace std;

int calculate(int value)
{
    int sum = 0;
    while (value > 0)
    {
        sum += value % 10;
        value /= 10;
    }
    return sum;
}

int main()
{
    int num, value;
    set<int> results;

    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> value;
        results.insert(calculate(value));
    }

    int count = 0;
    cout << results.size() << endl;
    for (int result : results)
    {
        if (count == 0)
        {
            cout << result;
        }
        else
        {
            cout << " " << result;
        }
        count++;
    }
    cout << endl;
    return 0;
}