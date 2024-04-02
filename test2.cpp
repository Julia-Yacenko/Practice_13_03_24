#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include "omp.h"

using namespace std;

bool cmp(pair<string, int>& a,
    pair<string, int>& b)
{
    return a.second > b.second;
}

void sort(map<string, int>& M)
{
    vector<pair<string, int> > A;

    for (auto& it : M) {
        A.push_back(it);
    }

    sort(A.begin(), A.end(), cmp);

    for (auto& it : A) {

        cout << it.first << ' '
            << it.second << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "rus"); 
    ifstream file("G:/file.txt"); 
    if (file.bad())
        std::cout << "Ошибка ввода-вывода при чтении\n";
    else if (file.fail())
        std::cout << "Неверный формат данных\n";

    map<string, int> word_list;
    string word;

#pragma omp parallel for
    while (file >> word)
    {
#pragma omp critical
        {
            if (word_list.find(word) != word_list.end())
            {
                word_list[word]++;
            }
            else
            {
                word_list[word] = 1;
            }
        }
    }

    sort(word_list);

    file.close();
	return 0;
}