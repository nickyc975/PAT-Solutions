#include <cstdio>
#include <iostream>

using namespace std;

bool check(string &value)
{
    int len = value.size() / 2;
    long long org = atoll(value.c_str());
    long long part_1 = atoll(value.substr(0, len).c_str());
    long long part_2 = atoll(value.substr(len, len).c_str());

    if (part_1 == 0 || part_2 == 0)
    {
        return false;
    }
    return (org % (part_1 * part_2)) == 0;
}

int main()
{
    int n;
    cin >> n;
    string value;
    for (int i = 0; i < n; i++)
    {
        cin >> value;
        printf(check(value) ? "Yes\n" : "No\n");
    }
    return 0;
}