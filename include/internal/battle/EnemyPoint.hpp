#pragma once
#include <bits/stdc++.h>
#include <internal/battle/NormalPoint.hpp>
#include <internal/battle/PatternPoint.hpp>
#include <internal/battle/EmergePoint.hpp>
#include <internal/card/Card.hpp>


using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class EnemyPoint : public NormalPoint{
public:
    bool prepareMoving = true;
    bool shootFlag = false;
    int movingUseStatus = 0;
    int times = 0;//必要?
    vector<PatternPoint> moving;

    void setPattern(vector<PatternPoint> move);

    void timer(vector<pair<double, double>> points, vector<int> large);

    void shoot();

    bool lose();

    void makeMove();

    void changeBullet();
};