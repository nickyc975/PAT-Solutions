#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class node
{
public:
    int addr, data, next;

    node(int addr, int data, int next): addr(addr), data(data), next(next) {}
};

int main()
{
    int head, node_num, k;
    cin >> head >> node_num >> k;

    vector<node *> neg, sml, lgr;
    unordered_map<int, node *> linkedlist;

    int addr, data, next;
    for (int i = 0; i < node_num; i++)
    {
        cin >> addr >> data >> next;
        linkedlist[addr] = new node(addr, data, next);
    }

    int cursor = head;
    while (cursor >= 0)
    {
        node *n = linkedlist[cursor];
        if (n->data < 0)
        {
            neg.push_back(n);
        }
        else if (n->data <= k)
        {
            sml.push_back(n);
        }
        else
        {
            lgr.push_back(n);
        }
        cursor = n->next;
    }

    for (node *n : sml)
    {
        neg.push_back(n);
    }

    for (node *n : lgr)
    {
        neg.push_back(n);
    }

    printf("%05d %d ", neg[0]->addr, neg[0]->data);
    for (int i = 1; i < neg.size(); i++)
    {
        printf("%05d\n%05d %d ", neg[i]->addr, neg[i]->addr, neg[i]->data);
    }
    printf("-1\n");
    return 0;
}