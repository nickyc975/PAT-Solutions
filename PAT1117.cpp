#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int total;
    cin >> total;

    int dist;
    vector<int> distances;
    for (int i = 0; i < total; i++)
    {
        cin >> dist;
        distances.push_back(dist);
    }

    sort(distances.begin(), distances.end());

    int count = 1;
    for (int i = distances.size() - 1; i >= 0 && count < distances[i]; i--)
    {
        count++;
    }
    cout << count - 1 << endl;
    return 0;
}