#include <iostream>
#include <unordered_set>

using namespace std;

int main()
{
    int forwards, skip, winner;
    unordered_set<string> winners;
    cin >> forwards >> skip >> winner;

    string nickname;
    for (int i = 1; i <= forwards; i++)
    {
        cin >> nickname;
        if (i == winner)
        {
            if (winners.find(nickname) == winners.end())
            {
                cout << nickname << endl;
                winners.insert(nickname);
                winner += skip;
            }
            else
            {
                winner++;
            }
        }
    }
    if (winners.size() <= 0)
    {
        cout << "Keep going..." << endl;
    }
    return 0;
}