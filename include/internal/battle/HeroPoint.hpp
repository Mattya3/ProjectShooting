#pragma once
#include <bits/stdc++.h>
#include <internal/battle/NormalPoint.hpp>
#include <internal/card/Card.hpp>

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class HeroPoint : public NormalPoint{
public:
    bool shootFlag = false;
    vector<int> level;
    vector<Card> list;
    bool moveFlag = true;

    void setCardlist(vector<Card> sets);

    void changeDirection(double per);

    int levelUp(int target);

    void timer(vector<pair<double, double>> points, vector<int> large);

    void contact(pair<double, double> point, int large);

    void shoot();
};