#include <cstdio>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main()
{
    set<int> singles;
    unordered_set<int> guests;
    unordered_map<int, int> couples;
    unordered_map<int, int>::iterator iter;

    int cp_num;
    cin >> cp_num;

    int p_1, p_2;
    for (int i = 0; i < cp_num; i++)
    {
        cin >> p_1 >> p_2;
        couples[p_1] = p_2;
        couples[p_2] = p_1;
    }

    int guest_num;
    cin >> guest_num;
    for (int i = 0; i < guest_num; i++)
    {
        cin >> p_1;
        guests.insert(p_1);
    }

    for (int guest : guests)
    {
        iter = couples.find(guest);
        if (iter == couples.end() || guests.find(iter->second) == guests.end())
        {
            singles.insert(guest);
        }
    }

    int count = 0;
    printf("%u\n", singles.size());
    for (int single : singles)
    {
        if (count == 0)
        {
            printf("%05d", single);
        }
        else
        {
            printf(" %05d", single);
        }
        count++;
    }
    return 0;
}