#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int main()
{
    int a, b, pair_num, query_num;
    unordered_map<int, unordered_set<int> *> incomp_table;

    cin >> pair_num >> query_num;
    for (int i = 0; i < pair_num; i++)
    {
        cin >> a >> b;
        if (incomp_table[a] == NULL)
        {
            incomp_table[a] = new unordered_set<int>();
        }
        incomp_table[a]->insert(b);

        if (incomp_table[b] == NULL)
        {
            incomp_table[b] = new unordered_set<int>();
        }
        incomp_table[b]->insert(a);
    }

    bool compatible;
    int good_num, good;
    unordered_set<int> incomp_goods;
    for (int i = 0; i < query_num; i++)
    {
        cin >> good_num;
        compatible = true;
        for (int j = 0; j < good_num; j++)
        {
            cin >> good;
            if (compatible)
            {
                if (incomp_goods.find(good) != incomp_goods.end())
                {
                    compatible = false;
                }
                else if (incomp_table.find(good) != incomp_table.end())
                {
                    incomp_goods.insert(incomp_table[good]->begin(), incomp_table[good]->end());
                }
            }
        }
        printf(compatible ? "Yes\n" : "No\n");
        incomp_goods.clear();
    }
    return 0;
}