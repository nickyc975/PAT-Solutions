#include <iostream>

using namespace std;

bool is_prime(int value)
{
    if (value <= 1)
    {
        return false;
    }

    for (int i = 2; i * i <= value; i++)
    {
        if (value % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int value;
    cin >> value;
    if (is_prime(value))
    {
        if (is_prime(value - 6))
        {
            cout << "Yes\n" << value - 6;
            return 0;
        }
        else if (is_prime(value + 6))
        {
            cout << "Yes\n" << value;
            return 0;
        }
    }

    cout << "No\n";
    while (!(is_prime(value) && (is_prime(value - 6) || is_prime(value + 6))))
    {
        value++;
    }
    cout << value;
    return 0;
}