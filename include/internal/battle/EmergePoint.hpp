#pragma once
#include <bits/stdc++.h>
#include <internal/battle/PatternPoint.hpp>
using namespace std;

class EmergePoint{
public:
    int emergeTime;
    int enemyId;
    pair<double, double> emergePosition;
    vector<PatternPoint> moving;


    int setFirst(string line);

    void putPattern(string line);

    vector<string> split(string str, char separator);
};
