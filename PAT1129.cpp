#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>

using namespace std;

class item
{
public:
    int id, freq = 1;
    item(int id): id(id){}
};

item *item_ptrs[50001] = {NULL};

bool cmp(const item *one, const item *another)
{
    return one->freq == another->freq ? one->id < another->id : one->freq > another->freq;
}

int main()
{
    int item_num, rec_num, it;
    set<item *, decltype(&cmp)> items(&cmp);

    cin >> item_num >> rec_num >> it;
    item_ptrs[it] = new item(it);
    items.insert(item_ptrs[it]);
    for (int i = 1; i < item_num; i++)
    {
        cin >> it;
        printf("%d:", it);
        set<item *>::iterator iter = items.begin();
        for (int j = 0; j < rec_num && iter != items.end(); j++)
        {
            printf(" %d", (*iter)->id);
            iter++;
        }
        printf("\n");

        if (item_ptrs[it] != NULL)
        {
            items.erase(item_ptrs[it]);
            item_ptrs[it]->freq++;
        }
        else
        {
            item_ptrs[it] = new item(it);
        }
        items.insert(item_ptrs[it]);
    }
    return 0;
}