#include <iostream>

using namespace std;

struct node
{
    string value;
    int lchild, rchild;
};

string compile(node tree[], int root)
{
    if (tree[root].lchild == -1 && tree[root].rchild == -1)
    {
        return tree[root].value;
    }

    string result = "(";

    if (tree[root].lchild != -1)
    {
        result += compile(tree, tree[root].lchild);
    }

    result += tree[root].value;

    if (tree[root].rchild != -1)
    {
        result += compile(tree, tree[root].rchild);
    }
    
    return result + ")";
}

int main()
{
    node tree[25];
    int node_num, has_parent[25] = {0};

    cin >> node_num;
    for (int i = 1; i <= node_num; i++)
    {
        cin >> tree[i].value >> tree[i].lchild >> tree[i].rchild;

        if (tree[i].lchild != -1)
        {
            has_parent[tree[i].lchild] = 1;
        }

        if (tree[i].rchild != -1)
        {
            has_parent[tree[i].rchild] = 1;
        }
    }

    for (int i = 1; i <= node_num; i++)
    {
        if (has_parent[i] == 0)
        {
            string result = compile(tree, i);
            if (result[0] == '(')
            {
                result = result.substr(1, result.size() - 2);
            }
            cout << result << endl;
            break;
        }
    }
    return 0;
}