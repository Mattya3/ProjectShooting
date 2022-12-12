#pragma once
#include <bits/stdc++.h>
#include <internal/battle/NormalPoint.hpp>
#include <internal/card/Card.hpp>

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class EnemyPoint : public NormalPoint{
public:
    int times = 0;
    int nowStatus;
    int movePattern = 1;
    int shootPattern = 1;

    void getEnemyData(int id);

    void timer(vector<pair<double, double>> points, vector<int> large);

    void shoot();

    void changeDirection();

    bool lose();

    void setMovePattern(int id);

    void setShootPattern(int id);
};