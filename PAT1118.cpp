#include <iostream>
#include <set>

#define MAX_BIRD_NUM 10001

using namespace std;

int tree_of_birds[MAX_BIRD_NUM] = {0};

int main()
{
    int tree_num = 0, bird_num = 0, tree_id = 1;

    int pic_num;
    cin >> pic_num;

    int num, bird;
    set<int> merge;
    for (int i = 0; i < pic_num; i++)
    {
        cin >> num;
        for (int j = 0; j < num; j++)
        {
            cin >> bird;
            if (tree_of_birds[bird] > 0)
            {
                merge.insert(tree_of_birds[bird]);
            }
            else
            {
                tree_of_birds[bird] = -1;
            }

            if (bird > bird_num)
            {
                bird_num = bird;
            }
        }

        for (int j = 1; j <= bird_num; j++)
        {
            int tree = tree_of_birds[j];
            if (tree == -1 || merge.find(tree) != merge.end())
            {
                tree_of_birds[j] = tree_id;
            }
        }
        tree_num = tree_num - merge.size() + 1;
        merge.clear();
        tree_id++;
    }

    cout << tree_num << " " << bird_num << endl;

    int query_num, b;
    cin >>  query_num;
    for (int i = 0; i < query_num; i++)
    {
        cin >> bird >> b;
        cout << (tree_of_birds[b] == tree_of_birds[bird] ? "Yes" : "No") << endl;
    }
    return 0;
}