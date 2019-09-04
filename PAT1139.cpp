#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, unordered_set<int> *> relations;

size_t my_hash(pair<int, int> *a)
{
    return abs(a->first) + abs(a->second);
}

bool my_equal(pair<int, int> *a, pair<int, int> *b)
{
    return a->first == b->first && a->second == b->second;
}

bool my_cmp(pair<int, int> *a, pair<int, int> *b)
{
    if (abs(a->first) == abs(b->first))
    {
        return abs(a->second) < abs(b->second);
    }
    return abs(a->first) < abs(b->first);
}

void contact(int a, int b)
{
    vector<pair<int, int> *> ordered_friends;
    unordered_map<int, unordered_set<int> *>::iterator a_friends, c_friends, d_friends;
    unordered_set<pair<int, int> *, decltype(&my_hash), decltype(&my_equal)> friends(sizeof(pair<int, int> *), my_hash, my_equal);

    a_friends = relations.find(a);
    if (a_friends != relations.end())
    {
        for (int c : *(a_friends->second))
        {
            if (c * a > 0 && c != b)
            {
                c_friends = relations.find(c);
                if (c_friends !=  relations.end())
                {
                    for (int d : *(c_friends->second))
                    {
                        if (d * b > 0 && d != a)
                        {
                            d_friends = relations.find(d);
                            if (d_friends != relations.end() && d_friends->second->find(b) != d_friends->second->end())
                            {
                                friends.insert(new pair<int, int>(c, d));
                            }
                        }
                    }
                }
            }
        }
    }

    for (pair<int, int> *f : friends)
    {
        ordered_friends.push_back(f);
    }

    sort(ordered_friends.begin(), ordered_friends.end(), my_cmp);

    printf("%d\n", ordered_friends.size());
    for (pair<int, int> *f : ordered_friends)
    {
        printf("%04d %04d\n", abs(f->first), abs(f->second));
    }
}

int main()
{
    int p_num, r_num;
    cin >> p_num >> r_num;

    int source, target;
    unordered_map<int, unordered_set<int> *>::iterator iter;
    for (int i = 0; i < r_num; i++)
    {
        cin >> source >> target;
        iter = relations.find(source);
        if (iter == relations.end())
        {
            relations[source] = new unordered_set<int>();
            iter = relations.find(source);
        }
        iter->second->insert(target);
        
        iter = relations.find(target);
        if (iter == relations.end())
        {
            relations[target] = new unordered_set<int>();
            iter = relations.find(target);
        }
        iter->second->insert(source);
    }

    int query_num;
    cin >> query_num;
    for (int i = 0; i < query_num; i++)
    {
        cin >> source >> target;
        contact(source, target);
    }
    return 0;
}