#include <iostream>
#include <queue>

using namespace std;

class Node
{
public:
    int value, height, id;
    Node *lchild, *rchild, *parent;

    Node(int value): 
        value(value), height(1), id(0),
        lchild(NULL), rchild(NULL), parent(NULL) {}

    int factor()
    {
        int l_height = 0, r_height = 0;
        if (this->lchild != NULL)
        {
            l_height = this->lchild->height;
        }

        if (this->rchild != NULL)
        {
            r_height = this->rchild->height;
        }
        return l_height - r_height;
    }

    void re_height()
    {
        int l_height = 0, r_height = 0;
        if (this->lchild != NULL)
        {
            l_height = this->lchild->height;
        }

        if (this->rchild != NULL)
        {
            r_height = this->rchild->height;
        }
        this->height = max(l_height, r_height) + 1;
    }
};

class AVLTree
{
public:
    Node *root;

    AVLTree(): root(NULL) {}

    void insert(int value)
    {
        if (root == NULL)
        {
            root = new Node(value);
        }
        else
        {
            _insert(root, value);
        }
    }

private:
    void _insert(Node *node, int value)
    {
        if (value < node->value)
        {
            if (node->lchild != NULL)
            {
                _insert(node->lchild, value);
            }
            else
            {
                node->lchild = new Node(value);
                node->lchild->parent = node;
            }
        }
        else if (value > node->value)
        {
            if (node->rchild != NULL)
            {
                _insert(node->rchild, value);
            }
            else
            {
                node->rchild = new Node(value);
                node->rchild->parent = node;
            }
        }
        node->re_height();
        rebalance(node);
    }

    void rebalance(Node *node)
    {
        if (node->factor() > 1)
        {
            if (node->lchild->factor() > 0)
            {
                rotateR(node);
            }
            else
            {
                rotateL(node->lchild);
                rotateR(node);
            }
        }
        else if (node->factor() < -1)
        {
            if (node->rchild->factor() < 0)
            {
                rotateL(node);
            }
            else
            {
                rotateR(node->rchild);
                rotateL(node);
            }
        }
    }

    void rotateR(Node *node)
    {
        Node **node_ptr = get_ptr(node);

        *node_ptr = node->lchild;
        (*node_ptr)->parent = node->parent;

        node->lchild = (*node_ptr)->rchild;
        if (node->lchild != NULL)
        {
            node->lchild->parent = node;
        }

        (*node_ptr)->rchild = node;
        node->parent = *node_ptr;

        node->re_height();
        (*node_ptr)->re_height();
    }

    void rotateL(Node *node)
    {
        Node **node_ptr = get_ptr(node);

        *node_ptr = node->rchild;
        (*node_ptr)->parent = node->parent;

        node->rchild = (*node_ptr)->lchild;
        if (node->rchild != NULL)
        {
            node->rchild->parent = node;
        }

        (*node_ptr)->lchild = node;
        node->parent = *node_ptr;

        node->re_height();
        (*node_ptr)->re_height();
    }

    Node **get_ptr(Node *node)
    {
        Node **ptr = &root;
        if (node->parent != NULL)
        {
            if (node == node->parent->lchild)
            {
                ptr = &(node->parent->lchild);
            }
            else
            {
                ptr = &(node->parent->rchild);
            }
        }
        return ptr;
    }
};

int main()
{
    int node_num;
    cin >> node_num;

    int value;
    AVLTree tree;
    for (int i = 0; i < node_num; i++)
    {
        cin >> value;
        tree.insert(value);
    }

    int count = 1;
    bool flag = true;
    queue<Node *> nodes;
    nodes.push(tree.root);
    while (!nodes.empty() && nodes.front() != NULL)
    {
        Node *node = nodes.front();
        node->id = count++;
        nodes.pop();

        if (node->parent == NULL)
        {
            cout << node->value;
        }
        else
        {
            cout << " " << node->value;
            if (flag && node->id < node->parent->id * 2)
            {
                flag = false;
            }
        }

        if (node->lchild != NULL)
        {
            nodes.push(node->lchild);
        }

        if (node->rchild != NULL)
        {
            nodes.push(node->rchild);
        }
    }

    cout << endl << (flag ? "YES" : "NO") << endl;
    return 0;
}