#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int node_num;
vector<int> pre_order, in_order;
unordered_map<int, int> in_idx_of;

int post_order()
{
    int pre_root_idx = 0, in_root_idx;
    int in_left = 0, in_right = node_num - 1;
    while (in_left != in_right)
    {
        in_root_idx = in_idx_of[pre_order[pre_root_idx]];
        if (in_root_idx > in_left)
        {
            in_right = in_root_idx - 1;
        }
        else
        {
            in_left = in_root_idx + 1;
        }
        pre_root_idx++;
    }
    return in_order[in_left];
}

int main()
{
    int value;
    cin >> node_num;
    for (int i = 0; i < node_num; i++)
    {
        cin >> value;
        pre_order.push_back(value);
    }
    for (int i = 0; i < node_num; i++)
    {
        cin >> value;
        in_order.push_back(value);
        in_idx_of[value] = i;
    }
    printf("%d", post_order());
    return 0;
}