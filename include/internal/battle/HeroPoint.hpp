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
    bool moveFlag = false;
    int stopShoot = 240;
    int shootpenalty = 0;

    void shooting(bool flag);
    
    void moving(bool flag);

    void setCardlist(vector<Card> sets);

    void changeDirection(double per);

    int levelUp(int target);

    void timer(vector<BulletPoint> &bullets);

    void contact(pair<double, double> point, int large);

    void shoot(vector<BulletPoint> &bullets);
};