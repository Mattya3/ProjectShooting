#pragma once
#include <bits/stdc++.h>
using namespace std;

class EmergePoint{//カードデータを保存する関数
public:
    int emergeTime;
    int enemyId;
    int hasPattern;
    vector<movePoint> moving;


    void setFirst(string line);

    void putPattern(string line);

    void wastePattern();

    vector<string> split(string str, char separator);
};
