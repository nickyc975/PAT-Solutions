#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int in_u_idx, in_v_idx;
vector<int> preorder, inorder;
unordered_map<int, int> inorder_idx;

void LCA(int in_left, int in_right, int pre_root_idx)
{
    if (in_left > in_right)
    {
        return;
    }

    int in_root_idx = inorder_idx[preorder[pre_root_idx]];
    if (in_u_idx < in_root_idx && in_v_idx < in_root_idx)
    {
        LCA(in_left, in_root_idx - 1, pre_root_idx + 1);
    }
    else if (in_u_idx > in_root_idx && in_v_idx > in_root_idx)
    {
        LCA(in_root_idx + 1, in_right, pre_root_idx + in_root_idx - in_left + 1);
    }
    else if ((in_u_idx < in_root_idx && in_v_idx > in_root_idx) 
        || (in_u_idx > in_root_idx && in_v_idx < in_root_idx))
    {
        printf("LCA of %d and %d is %d.\n", inorder[in_u_idx], inorder[in_v_idx], inorder[in_root_idx]);
    }
    else if (in_u_idx == in_root_idx)
    {
        printf("%d is an ancestor of %d.\n", inorder[in_u_idx], inorder[in_v_idx]);
    }
    else
    {
        printf("%d is an ancestor of %d.\n", inorder[in_v_idx], inorder[in_u_idx]);
    }
}

int main()
{
    int value, node_num, query_num;
    cin >> query_num >> node_num;
    for (int i = 0; i < node_num; i++)
    {
        cin >> value;
        inorder_idx[value] = i;
        inorder.push_back(value);
    }
    for (int i = 0; i < node_num; i++)
    {
        cin >> value;
        preorder.push_back(value);
    }
    int u, v;
    unordered_map<int, int>::iterator u_it, v_it;
    for (int i = 0; i < query_num; i++)
    {
        cin >> u >> v;
        u_it = inorder_idx.find(u);
        v_it = inorder_idx.find(v);
        if (u_it == inorder_idx.end() && v_it == inorder_idx.end())
        {
            printf("ERROR: %d and %d are not found.\n", u, v);
        }
        else if (u_it == inorder_idx.end())
        {
            printf("ERROR: %d is not found.\n", u);
        }
        else if (v_it == inorder_idx.end())
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