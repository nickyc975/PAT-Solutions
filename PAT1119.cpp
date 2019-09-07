#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Node
{
public:
    int value;
    Node *lchild, *rchild;
    
    Node(int value): value(value), lchild(NULL), rchild(NULL) {}
};

bool unique = true;
vector<int> preorder, postorder;
unordered_map<int, int> pre_index_of, post_index_of;

Node *build_tree(int pre_l, int pre_r)
{
    Node *node = new Node(preorder[pre_l]);
    if (pre_l >= pre_r)
    {
        return node;
    }

    int post_root = post_index_of[preorder[pre_l]];
    if (preorder[pre_l + 1] != postorder[post_root - 1])
    {
        int pre_r_child_idx = pre_index_of[postorder[post_root - 1]];
        node->lchild = build_tree(pre_l + 1, pre_r_child_idx - 1);
        node->rchild = build_tree(pre_r_child_idx, pre_r);
    }
    else
    {
        node->lchild = build_tree(pre_l + 1, pre_r);
        unique = false;
    }
    return node;
}

void inorder(Node *root)
{
    if (root->lchild != NULL)
    {
        inorder(root->lchild);
        cout << " ";
    }

    cout << root->value;

    if (root->rchild != NULL)
    {
        cout << " ";
        inorder(root->rchild);
    }
}

int main()
{
    int node_num, value;

    cin >> node_num;
    for (int i = 0; i < node_num; i++)
    {
        cin >> value;
        preorder.push_back(value);
        pre_index_of[value] = i;
    }
    for (int i = 0; i < node_num; i++)
    {
        cin >> value;
        postorder.push_back(value);
        post_index_of[value] = i;
    }
    Node *root = build_tree(0, node_num - 1);
    cout << (unique ? "Yes" : "No") << endl;
    inorder(root);
    cout << endl;
    return 0;
}