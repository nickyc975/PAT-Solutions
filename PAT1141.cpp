#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class institution
{
public:
    string name;
    float tws = 0.0;
    int testee_num = 0;

    institution(string name) : name(name){}

    int get_tws()
    {
        return (int)(this->tws);
    }
};

bool cmp(institution *a, institution *b)
{
    if (a->get_tws() == b->get_tws())
    {
        if (a->testee_num == b->testee_num)
        {
            return a->name < b->name;
        }
        return a->testee_num < b->testee_num;
    }
    return a->get_tws() > b->get_tws();
}

int main()
{
    vector<institution *> insts;
    unordered_map<string, institution *> inst_names;
    unordered_map<string, institution *>::iterator it;

    int num, score;
    string id, inst_name;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cin >> id >> score >> inst_name;
        for (int j = 0; j < inst_name.size(); j++)
        {
            inst_name[j] = tolower(inst_name[j]);
        }

        it = inst_names.find(inst_name);
        if (it == inst_names.end())
        {
            inst_names[inst_name] = new institution(inst_name);
            it = inst_names.find(inst_name);
            insts.push_back(it->second);
        }

        switch (id[0])
        {
        case 'B':
            it->second->tws += score / 1.5;
            break;
        case 'A':
            it->second->tws += score * 1.0;
            break;
        case 'T':
            it->second->tws += score * 1.5;
            break;
        default:
            break;
        }
        it->second->testee_num++;
    }

    sort(insts.begin(), insts.end(), cmp);

    int rank = 1;
    printf("%d\n", insts.size());
    printf("%d %s %d %d\n", rank, insts[0]->name.c_str(), insts[0]->get_tws(), insts[0]->testee_num);
    for (int i = 1; i < insts.size(); i++)
    {
        if (insts[i]->get_tws() != insts[i - 1]->get_tws())
        {
            rank = i + 1;
        }
        printf("%d %s %d %d\n", rank, insts[i]->name.c_str(), insts[i]->get_tws(), insts[i]->testee_num);
    }
    return 0;
}