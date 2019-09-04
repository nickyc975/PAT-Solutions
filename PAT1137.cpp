#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class student
{
public:
    const string stu_id;
    int g = 0, g_p = -1, g_mid = -1, g_final = -1;

    student(string stu_id): stu_id(stu_id){}
};

bool cmp(student *a, student *b)
{
    if (a->g == b->g)
    {
        return a->stu_id < b->stu_id;
    }
    return a->g > b->g;
}

int main()
{
    vector<student *> qualified;
    unordered_map<string, student *> students;
    unordered_map<string, student *>::iterator iter;

    int p_num, m_num, f_num;
    cin >> p_num >> m_num >> f_num;

    int score;
    string stu_id;
    for (int i = 0; i < p_num; i++)
    {
        cin >> stu_id >> score;
        iter = students.find(stu_id);
        if (iter == students.end())
        {
            students[stu_id] = new student(stu_id);
            iter = students.find(stu_id);
        }
        iter->second->g_p = score;
    }

    for (int i = 0; i < m_num; i++)
    {
        cin >> stu_id >> score;
        iter = students.find(stu_id);
        if (iter == students.end())
        {
            students[stu_id] = new student(stu_id);
            iter = students.find(stu_id);
        }
        iter->second->g_mid = score;
    }

    for (int i = 0; i < f_num; i++)
    {
        cin >> stu_id >> score;
        iter = students.find(stu_id);
        if (iter == students.end())
        {
            students[stu_id] = new student(stu_id);
            iter = students.find(stu_id);
        }
        iter->second->g_final = score;

        if (iter->second->g_mid > iter->second->g_final)
        {
            iter->second->g = round(iter->second->g_mid * 0.4 + iter->second->g_final * 0.6);
        }
        else
        {
            iter->second->g = iter->second->g_final;
        }

        if (iter->second->g_p >= 200 && iter->second->g >= 60)
        {
            qualified.push_back(iter->second);
        }
    }
    
    sort(qualified.begin(), qualified.end(), cmp);

    for (student *stu : qualified)
    {
        printf("%s %d %d %d %d\n", stu->stu_id.c_str(), stu->g_p, stu->g_mid, stu->g_final, stu->g);
    }
    return 0;
}