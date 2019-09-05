#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class node_t
{
public:
    int value, level;
    node_t *lchild, *rchild;
    node_t(int value, int level): value(value), level(level), lchild(NULL), rchild(NULL) {}
};

int level = 1;
vector<int> inorder, postorder;
unordered_map<int, int> index_of;

node_t *build_tree(int inl, int inr, int post_root)
{
    int in_root = index_of[postorder[post_root]];
    node_t *node = new node_t(postorder[post_root], level);

    level++;
    if (in_root > inl)
    {
        node->lchild = build_tree(inl, in_root - 1, post_root - inr + in_root - 1);
    }

    if (in_root < inr)
    {
        node->rchild = build_tree(in_root + 1, inr, post_root - 1);
    }
    level--;

    return node;
}

int main()
{
    int node_num, n;
    cin >> node_num;
    for (int i = 0; i < node_num; i++)
    {
        cin >> n;
        inorder.push_back(n);
        index_of[n] = i;
    }
    for (int i = 0; i < node_num; i++)
    {
        cin >> n;
        postorder.push_back(n);
    }

    stack<int> s;
    queue<node_t *> q;
    node_t *root = build_tree(0, node_num - 1, node_num - 1);

    cout << root->value;
    if (root->lchild != NULL)
    {
        q.push(root->lchild);
    }

    if (root->rchild != NULL)
    {
        q.push(root->rchild);
    }

    while (!q.empty())
    {
        if (q.front()->level % 2 == 0)
        {
            while (!q.empty() && q.front()->level % 2 == 0)
            {
                node_t *node = q.front();
                if (node->lchild != NULL)
                {
                    q.push(node->lchild);
                }

                if (node->rchild != NULL)
                {
                    q.push(node->rchild);
                }
                cout << " " << node->value;
                q.pop();
            }
        }
        else
        {
            while (!q.empty() && q.front()->level % 2 != 0)
            {
                node_t *node = q.front();
                if (node->lchild != NULL)
                {
                    q.push(node->lchild);
                }

                if (node->rchild != NULL)
                {
                    q.push(node->rchild);
                }
                s.push(node->value);
                q.pop();
            }

            while (!s.empty())
            {
                cout << " " << s.top();
                s.pop();
            }
        }
    }
    cout << endl;
    return 0;
}