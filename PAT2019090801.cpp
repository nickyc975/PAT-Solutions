#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int gcd(int a, int b)
{
    int mod, m = max(a, b), n = min(a, b);
    while(n != 0)
    {
        mod = m % n;
        m = n; n = mod;
    }
    return m;
}

bool is_prime(int value)
{
    if (value <= 2)
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

int di_sum(int value)
{
    int sum = 0;
    while (value > 0)
    {
        sum += value % 10;
        value /= 10;
    }
    return sum;
}

int init_n(int m, int k, int t)
{
    char digits[k + 1];
    digits[0] = '1'; digits[k] = 0;
    int left = m - 1, cursor = k - 1;
    while (left > 9 && cursor > k - t - 1)
    {
        digits[cursor--] = '9';
        left -= 9;
    }

    while (left > 8 && cursor > 0)
    {
        digits[cursor--] = '8';
        left -= 8;
    }
    
    if (left > 0 && cursor > 0)
    {
        digits[cursor] = '0' + left;
    }
    
    return atoi(digits);
}

int main()
{
    int num;
    cin >>num;

    int k, m;
    for (int i = 0; i < num ; i++)
    {
        cin >> k >> m;
        cout << "Case " << i + 1 << endl;

        int t = 1;
        map<int, vector<int> *> ns;
        while (t * 9 < m)
        {
            int n = m - (t * 9) + 1;
            if (is_prime(gcd(m, n)))
            {
                ns[n] = new vector<int>();
                ns[n]->push_back(t);
            }
            t++;
        }

        int upper = pow(10, k);
        for (pair<int, vector<int> *> item : ns)
        {
            t = item.second->back();
            item.second->pop_back();
            int init = init_n(m, k, t), inc = pow(10, t);
            while (init < upper)
            {
                if (di_sum(init) == m && di_sum(init + 1) == item.first)
                {
                    item.second->push_back(init);
                }
                init += inc;
            }
            
        }

        int count = 0;
        map<int, vector<int> *>::iterator iter = ns.begin();
        while (iter != ns.end())
        {
            for (int j = 0; j < iter->second->size(); j++)
            {
                count++;
                cout << iter->first << " " << iter->second->at(j) << endl;
            }
            iter++;
        }

        if (count <= 0)
        {
            cout << "No Solution" << endl;
        }
    }
    return 0;
}

/**
1
9 77
33 699899999
33 789899999
33 798899999
33 799799999
33 879899999
33 888899999
33 889799999
33 897899999
33 898799999
33 899699999
33 969899999
33 978899999
33 979799999
33 987899999
33 988799999
33 989699999
33 996899999
33 997799999
33 998699999
33 999599999
42 699989999
42 789989999
42 798989999
42 799889999
42 799979999
42 879989999
42 888989999
42 889889999
42 889979999
42 897989999
42 898889999
42 898979999
42 899789999
42 899879999
42 899969999
42 969989999
42 978989999
42 979889999
42 979979999
42 987989999
42 988889999
42 988979999
42 989789999
42 989879999
42 989969999
42 996989999
42 997889999
42 997979999
42 998789999
42 998879999
42 998969999
42 999689999
42 999779999
42 999869999
42 999959999

// solve
33 699899999
33 789899999
33 798899999
33 799799999
33 879899999
33 888899999
33 889799999
33 897899999
33 898799999
33 899699999
33 969899999
33 978899999
33 979799999
33 987899999
33 988799999
33 989699999
33 996899999
33 997799999
33 998699999
33 999599999
42 699989999
42 789989999
42 798989999
42 799889999
42 799979999
42 879989999
42 888989999
42 889889999
42 889979999
42 897989999
42 898889999
42 898979999
42 899789999
42 899879999
42 899969999
42 969989999
42 978989999
42 979889999
42 979979999
42 987989999
42 988889999
42 988979999
42 989789999
42 989879999
42 989969999
42 996989999
42 997889999
42 997979999
42 998789999
42 998879999
42 998969999
42 999689999
42 999779999
42 999869999
42 999959999
 */