#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_map>

using namespace std;

class Contestant
{
public:
    int id;
    string award;
    bool checked = false;

    Contestant(int id, int rank)
    {
        this->id = id;
        if (rank == 1)
        {
            this->award = "Mystery Award";
        }
        else if (is_prime(rank))
        {
            this->award = "Minion";
        }
        else
        {
            this->award = "Chocolate";
        }
    }

    static bool is_prime(int value)
    {
        for (int i = 2; i * i <= value; i++)
        {
            if (value % i == 0)
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    int total_num;
    cin >> total_num;

    int id;
    unordered_map<int, Contestant *> contestants;
    unordered_map<int, Contestant *>::iterator iter;
    for (int i = 0; i < total_num; i++)
    {
        cin >> id;
        contestants[id] = new Contestant(id, i + 1);
    }

    int query_num;
    cin >> query_num;
    for (int i = 0; i < query_num; i++)
    {
        cin >> id;
        iter = contestants.find(id);
        if (iter == contestants.end())
        {
            printf("%04d: Are you kidding?\n", id);
        }
        else
        {
            if (!(iter->second->checked))
            {
                printf("%04d: %s\n", id, iter->second->award.c_str());
                iter->second->checked = true;
            }
            else
            {
                printf("%04d: Checked\n", id);
            }
        }
    }
    return 0;
}