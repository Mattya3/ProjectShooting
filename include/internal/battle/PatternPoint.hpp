#pragma once
#include <bits/stdc++.h>
using namespace std;

class PatternPoint{//カードデータを保存する関数
public:
    double changeHpLine;
    int hasPattern;
    int nowPattern;
    vector<int> moveId;
    vector<int> shootId;
    vector<int> loopNum;

    void putPattern(string line);

    void changePattern();

    vector<string> split(string str, char separator);
};
