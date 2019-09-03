#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int in_u_idx, in_v_idx;
vector<int> pre_order, in_order;
unordered_map<int, int> in_idx_of;

bool cmp(int a, int b)
{
    return a < b;
}

void LCA(int in_left, int in_right, int pre_root_idx)
{
    if (in_left > in_right)
    {
        return;
    }

    int in_root_idx = in_idx_of[pre_order[pre_root_idx]];
    if (in_u_idx < in_root_idx && in_v_idx < in_root_idx)
    {
        LCA(in_left, in_root_idx - 1, pre_root_idx + 1);
    }
    else if (in_u_idx > in_root_idx && in_v_idx > in_root_idx)
    {
        LCA(in_root_idx + 1, in_right, pre_root_idx + in_root_idx - in_left + 1);
    }
    else if (in_u_idx == in_root_idx)
    {
        printf("%d is an ancestor of %d.\n", in_order[in_u_idx], in_order[in_v_idx]);
    }
    else if (in_v_idx == in_root_idx)
    {
        printf("%d is an ancestor of %d.\n", in_order[in_v_idx], in_order[in_u_idx]);
    }
    else
    {
        printf("LCA of %d and %d is %d.\n", in_order[in_u_idx], in_order[in_v_idx], in_order[in_root_idx]);
    }
}

int main()
{
    int value;
    int query_num, node_num;
    cin >> query_num >> node_num;
    for (int i = 0; i < node_num; i++)
    {
        cin >> value;
        pre_order.push_back(value);
        in_order.push_back(value);
    }
    sort(in_order.begin(), in_order.end(), cmp);
    for (int i = 0; i < in_order.size(); i++)
    {
        in_idx_of[in_order[i]] = i;
    }

    int u, v;
    unordered_map<int, int>::iterator u_it, v_it;
    for (int i = 0; i < query_num; i++)
    {
        cin >> u >> v;
        u_it = in_idx_of.find(u);
        v_it = in_idx_of.find(v);
        if (u_it == in_idx_of.end() && v_it == in_idx_of.end())
        {
            printf("ERROR: %d and %d are not found.\n", u, v);
        }
        else if (u_it == in_idx_of.end())
        {
            printf("ERROR: %d is not found.\n", u);
        }
        else if (v_it == in_idx_of.end())
        {
            printf("ERROR: %d is not found.\n", v);
        }
        else
        {
            in_u_idx = u_it->second;
            in_v_idx = v_it->second;
            LCA(0, node_num - 1, 0);
        }
    }
    return 0;
}