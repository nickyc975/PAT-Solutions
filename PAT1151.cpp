#include <iostream>
#include <unordered_map>

using namespace std;

class Node
{
public:
    int level;
    const int value;
    Node *parent, *lchild, *rchild;

    Node(int value): 
        value(value),
        parent(NULL), 
        lchild(NULL), 
        rchild(NULL)
    {

    }
};

unordered_map<int, Node *> nodes;

int LCA(Node *root, int u, int v)
{
    unordered_map<int, Node *>::iterator it;
    Node *node_u = NULL, *node_v = NULL;

    it = nodes.find(u);
    if (it != nodes.end())
    {
        node_u = it->second;
    }

    it = nodes.find(v);
    if (it != nodes.end())
    {
        node_v = it->second;
    }

    if (node_u == NULL && node_v == NULL)
    {
        printf("ERROR: %d and %d are not found.\n", u, v);
    }
    else if (node_u == NULL)
    {
        printf("ERROR: %d is not found.\n", u);
    }
    else if (node_v == NULL)
    {
        printf("ERROR: %d is not found.\n", v);
    }
    else
    {
        while (node_u->value != node_v->value)
        {
            if (node_u->level > node_v->level)
            {
                node_u = node_u->parent;
            }
            else if (node_u->level < node_v->level)
            {
                node_v = node_v->parent;
            }
            else
            {
                node_u = node_u->parent;
                node_v = node_v->parent;
            }
        }

        if (node_u->value == u)
        {
            printf("%d is an ancestor of %d.\n", u, v);
        }
        else if (node_u->value == v)
        {
            printf("%d is an ancestor of %d.\n", v, u);
        }
        else
        {
            printf("LCA of %d and %d is %d.\n", u, v, node_u->value);
        }
    }
}

int main()
{
    int query_num, node_num;
    unordered_map<int, int> in_order;
    int value, pre_value, index, pre_index;
    Node *root = NULL, *node = NULL, *pre_node = NULL;

    cin >> query_num >> node_num;
    for (int i = 0; i < node_num; i++)
    {
        cin >> value;
        in_order[value] = i;
    }

    cin >> pre_value;
    root = new Node(pre_value);
    root->level = 1;
    nodes[pre_value] = root;

    pre_node = root;
    pre_index = in_order[pre_value];
    for (int i = 1; i < node_num; i++)
    {
        cin >> value;
        node = new Node(value);
        nodes[value] = node;

        index = in_order[value];
        if (index < pre_index)
        {
            pre_node->lchild = node;
        }
        else
        {
            while (pre_node->parent != NULL && in_order[pre_node->parent->value] < index)
            {
                pre_node = pre_node->parent;
            }
            
            while (pre_node->rchild != NULL)
            {
                pre_node = pre_node->rchild;
            }
            
            pre_node->rchild = node;
        }

        node->parent = pre_node;
        node->level = pre_node->level + 1;
        pre_index = index;
        pre_node = node;
    }

    int u, v;
    for (int i = 0; i < query_num; i++)
    {
        cin >> u >> v;
        LCA(root, u, v);
    }

    return 0;
}
