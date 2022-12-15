#pragma once
#include <bits/stdc++.h>
using namespace std;

class PatternPoint{//パターンデータを保存する関数
public:
    double changeHpLine;
    int nowPattern = 0;//現在どのmoveIdに対応しているか
    int nowLoop = 0;//同一のmoveIdが何回目なのか
    vector<int> moveId;
    vector<int> shootId;
    vector<int> loopNum;//何回loopする予定なのか

    void putPattern(string line);

    void changeLoop();

    vector<string> split(string str, char separator);
};
