#include <algorithm>
#include <map>
#include <stdio.h>
#include <vector>

using namespace std;

class Testee
{
public:
    char level;
    int site, date, number, score;

    Testee(const char card_num[], int score)
    {
        this->level = card_num[0];
        this->site = (card_num[1] - '0') * 100 + (card_num[2] - '0') * 10 + (card_num[3] - '0');
        this->date = (card_num[4] - '0') * 100000 + (card_num[5] - '0') * 10000 + (card_num[6] - '0') * 1000 + (card_num[7] - '0') * 100 + (card_num[8] - '0') * 10 + (card_num[9] - '0');
        this->number = (card_num[10] - '0') * 100 + (card_num[11] - '0') * 10 + (card_num[12] - '0');
        this->score = score;
    }
};

bool cmp_score(Testee *a, Testee *b)
{
    if (a->score == b->score)
    {
        if (a->site == b->site)
        {
            if (a->date == b->date)
            {
                return a->number < b->number;
            }
            return a->date < b->date;
        }
        return a->site < b->site;
    }
    return a->score > b->score;
}

bool cmp_nums(pair<int, int> *a, pair<int, int> *b)
{
    if (a->second == b->second)
    {
        return a->first < a->first;
    }
    return a->second > b->second;
}

int main()
{
    char card_num[14];
    int testee_num, query_num, score;
    map<char, vector<Testee *> *> levels;
    map<int, vector<Testee *> *> sites, dates;

    scanf("%d %d", &testee_num, &query_num);
    for (int i = 0; i < testee_num; i++)
    {
        scanf("\n%s %d", card_num, &score);
        Testee *testee = new Testee(card_num, score);
        if (levels[testee->level] == nullptr)
        {
            levels[testee->level] = new vector<Testee *>();
        }
        levels[testee->level]->push_back(testee);

        if (sites[testee->site] == nullptr)
        {
            sites[testee->site] = new vector<Testee *>();
        }
        sites[testee->site]->push_back(testee);

        if (dates[testee->date] == nullptr)
        {
            dates[testee->date] = new vector<Testee *>();
        }
        dates[testee->date]->push_back(testee);
    }

    char level;
    int case_num, site, date;
    for (int i = 0; i < query_num; i++)
    {
        scanf("%d ", &case_num);
        switch(case_num)
        {
            case 1:
            {
                scanf("%c", &level);
                printf("Case %d: %d %c\n", i + 1, case_num, level);
                auto testees = levels[level];
                if (testees == nullptr || testees->size() <= 0)
                {
                    printf("NA\n");
                }
                else
                {
                    sort(testees->begin(), testees->end(), cmp_score);
                    vector<Testee *>::iterator it = testees->begin();
                    while (it != testees->end())
                    {
                        printf("%c%03d%06d%03d %d\n", (*it)->level, (*it)->site, (*it)->date, (*it)->number, (*it)->score);
                        it++;
                    }
                }
                break;
            }
            case 2:
            {
                scanf("%d", &site);
                printf("Case %d: %d %03d\n", i + 1, case_num, site);
                auto testees = sites[site];
                if (testees == nullptr || testees->size() <= 0)
                {
                    printf("NA\n");
                }
                else
                {
                    int total_num = 0, total_score = 0;
                    vector<Testee *>::iterator it = testees->begin();
                    while (it != testees->end())
                    {
                        total_score += (*it)->score;
                        total_num++;
                        it++;
                    }
                    printf("%d %d\n", total_num, total_score);
                }
                break;
            }
            case 3:
            {
                scanf("%d", &date);
                printf("Case %d: %d %06d\n", i + 1, case_num, date);
                auto testees = dates[date];
                if (testees == nullptr || testees->size() <= 0)
                {
                    printf("NA\n");
                }
                else
                {
                    map<int, int> nums;
                    vector<Testee *>::iterator it = testees->begin();
                    while (it != testees->end())
                    {
                        if (nums.find((*it)->site) == nums.end())
                        {
                            nums[(*it)->site] = 0;
                        }
                        nums[(*it)->site]++;
                        it++;
                    }
                    
                    vector<pair<int, int> *> pairs;
                    map<int, int>::iterator map_it = nums.begin();
                    while (map_it != nums.end())
                    {
                        pairs.push_back(new pair<int, int>(map_it->first, map_it->second));
                        map_it++;
                    }

                    sort(pairs.begin(), pairs.end(), cmp_nums);
                    vector<pair<int, int> *>::iterator itt = pairs.begin();
                    while (itt != pairs.end())
                    {
                        printf("%d %d\n", (*itt)->first, (*itt)->second);
                        itt++;
                    }
                }
                break;
            }
            default:
                break;
        }
    }

    return 0;
}