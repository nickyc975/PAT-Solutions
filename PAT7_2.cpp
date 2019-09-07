#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    unordered_set<string> alumnus, guests, comes;

    int num;
    string id;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> id;
        alumnus.insert(id);
    }

    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> id;
        guests.insert(id);
        if (alumnus.find(id) != alumnus.end())
        {
            comes.insert(id);
        }
    }

    id = "999999999999999999";
    cout << comes.size() << endl;
    if (comes.size() > 0)
    {
        for (string s : comes)
        {
            if (s.substr(6, 8) < id.substr(6, 8))
            {
                id = s;
            }
        }
    }
    else
    {
        for (string s : guests)
        {
            if (s.substr(6, 8) < id.substr(6, 8))
            {
                id = s;
            }
        }
    }
    cout << id;
    return 0;
}