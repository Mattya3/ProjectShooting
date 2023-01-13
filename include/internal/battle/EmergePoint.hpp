#pragma once
#include <bits/stdc++.h>
#include <internal/battle/PatternPoint.hpp>
#include <internal/Split.hpp>
using namespace std;

class EmergePoint{
private:
    short emergeTime;
    short enemyId;
    pair<double, double> emergePosition;
    vector<PatternPoint> moving;

public:
    short setFirst(string line);

    void putPattern(string line);

    short comeTime();

    short comeEnemyId();

    pair<double, double> comePosition();

    vector<PatternPoint> comeMovePattern();
};
