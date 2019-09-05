#include <algorithm>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

enum color
{
    red,
    black
};

vector<int> preorder, inorder;
unordered_map<int, int> indexof;
unordered_map<int, color> colorof;

bool cmp(int a, int b)
{
    return a < b;
}

int check(int inl, int inr, int pre_root, bool &flag)
{
    if (inl >= inr)
    {
        return colorof[inorder[inl]] == black ? 2 : 1;
    }

    int in_root = indexof[preorder[pre_root]];
    color cur_color = colorof[preorder[pre_root]];
    int l_child = pre_root + 1, r_child = pre_root + in_root - inl + 1;
    if (cur_color == red)
    {
        if (l_child == r_child || !(colorof[preorder[l_child]] == black && colorof[preorder[r_child]] == black))
        {
            flag = false;
            return 0;
        }
    }

    int l_cnt = 1, r_cnt = 1;
    if (inl < in_root)
    {
        l_cnt = check(inl, in_root - 1, l_child, flag);
    }

    if (inr > in_root)
    {
        r_cnt = check(in_root + 1, inr, r_child, flag);
    }

    if (flag)
    {
        flag = l_cnt == r_cnt;
    }
    return cur_color == black ? l_cnt + 1 : l_cnt;
}

int main()
{
    bool flag = true;
    int query_num, node_num, value;
    cin >> query_num;
    for (int i = 0; i < query_num; i++)
    {
        cin >> node_num;
        for (int j = 0; j < node_num; j++)
        {
            cin >> value;
            preorder.push_back(abs(value));
            inorder.push_back(abs(value));
            colorof[abs(value)] = value < 0 ? red : black;
        }
        sort(inorder.begin(), inorder.end(), cmp);
        for (int j = 0; j < node_num; j++)
        {
            indexof[inorder[j]] = j;
        }
        if (colorof[preorder[0]] == red)
        {
            flag = false;
        }
        else
        {
            check(0, node_num - 1, 0, flag);
        }
        printf(flag ? "Yes\n" : "No\n");

        flag = true;
        preorder.clear();
        inorder.clear();
        indexof.clear();
        colorof.clear();
    }
    return 0;
}
