#include <iostream>

using namespace std;

int vert_num, edge_num;
int visited_cnt = 0, visited[512] = {0};
int vertices[512] = {0}, edges[512][512] = {{0}};

void visit(int vert)
{
    visited_cnt++;
    visited[vert] = 1;
    for (int i = 1; i <= vert_num; i++)
    {
        if (edges[vert][i] != 0 && visited[i] == 0)
        {
            visit(i);
        }
    }
}

int main()
{
    int source, target;
    cin >> vert_num >> edge_num;
    for (int i = 0; i < edge_num; i++)
    {
        cin >> source >> target;
        vertices[source]++;
        vertices[target]++;
        edges[source][target] = 1;
        edges[target][source] = 1;
    }

    int odd_cnt = 0;
    for (int i = 1; i <= vert_num; i++)
    {
        if (i != 1)
        {
            cout << " ";
        }
        cout << vertices[i];
        odd_cnt += vertices[i] % 2 == 0 ? 0 : 1;
    }
    cout << endl;
    if (odd_cnt > 2 || odd_cnt == 1)
    {
        cout << "Non-Eulerian" << endl;
    }
    else
    {
        visit(1);
        if (visited_cnt < vert_num)
        {
            cout << "Non-Eulerian" << endl;
        }
        else if (odd_cnt == 2)
        {
            cout << "Semi-Eulerian" << endl;
        }
        else
        {
            cout << "Eulerian" << endl;
        }
    }
    return 0;
}