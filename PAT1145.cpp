#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

class hashtable
{
private:
    int size;
    int *table;
    const int to_prime(int value);
    const bool is_prime(int value);

public:
    hashtable(int size);
    bool insert(int value);
    bool find(int value, int &step_cnt);
};

hashtable::hashtable(int size)
{
    this->size = to_prime(size);
    this->table = (int *)malloc(this->size * sizeof(int));
    memset(this->table, -1, this->size * sizeof(int));
}

bool hashtable::insert(int value)
{
    int index;
    for (int i = 0; i < this->size; i++)
    {
        index = (value + i * i) % this->size;
        if (this->table[index] == -1)
        {
            this->table[index] = value;
            return true;
        }
    }
    return false;
}

bool hashtable::find(int value, int &step_cnt)
{
    int index;
    for (int i = 0; i < this->size; i++)
    {
        index = (value + i * i) % this->size;
        if (this->table[index] == value)
        {
            step_cnt = i + 1;
            return true;
        }
        else if (this->table[index] == -1)
        {
            step_cnt = i + 1;
            return false;
        }
    }
    step_cnt = this->size + 1;
    return false;
}

const int hashtable::to_prime(int value)
{
    while (!is_prime(value))
    {
        if (value % 2 == 0)
        {
            value += 1;
        }
        else
        {
            value += 2;
        }
    }
    return value;
}

const bool hashtable::is_prime(int value)
{
    if (value <= 1)
    {
        return false;
    }

    if (value == 2)
    {
        return true;
    }

    int bound = sqrt(value) + 1;
    for (int i = 2; i <= bound; i++)
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
    int size, key_num, query_num;
    cin >> size >> key_num >> query_num;

    int key;
    hashtable table(size);
    for (int i = 0; i < key_num; i++)
    {
        cin >> key;
        if (!table.insert(key))
        {
            printf("%d cannot be inserted.\n", key);
        }
    }

    int total_step = 0, step_cnt;
    for (int i = 0; i < query_num; i++)
    {
        cin >> key;
        table.find(key, step_cnt);
        total_step += step_cnt;
    }

    printf("%.1f", (float)total_step / (float)query_num);
    return 0;
}