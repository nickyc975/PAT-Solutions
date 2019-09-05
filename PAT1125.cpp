#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int num, len;
    cin >> num;
    vector<double> ropes;
    greater<double> cmp = greater<double>();
    make_heap(ropes.begin(), ropes.end(), cmp);

    for (int i = 0; i < num; i++)
    {
        cin >> len;
        ropes.push_back(len);
        push_heap(ropes.begin(), ropes.end(), cmp);
    }

    double r1, r2;
    while (ropes.size() > 1)
    {
        pop_heap(ropes.begin(), ropes.end(), cmp);
        r1 = ropes.back();
        ropes.pop_back();

        pop_heap(ropes.begin(), ropes.end(), cmp);
        r2 = ropes.back();
        ropes.pop_back();

        ropes.push_back((r1 + r2) / 2);
        push_heap(ropes.begin(), ropes.end(), cmp);
    }

    pop_heap(ropes.begin(), ropes.end(), cmp);
    cout << (int)ropes.back() << endl;
    return 0;
}