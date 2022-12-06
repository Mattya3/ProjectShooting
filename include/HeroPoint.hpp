#pragma once
#include <bits/stdc++.h>
#include "NormalPoint.hpp"
#include "Card.hpp"

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class HeroPoint : public NormalPoint{
public:
    bool shootFlag = true;
    vector<int> level;
    vector<Card> list;
    

    void setCardlist(vector<Card> sets);

    int levelUp(int target);

    void timer(vector<pair<double, double>> points, vector<int> large);

    void contact(pair<double, double> point, int large);
};