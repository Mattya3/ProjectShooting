#pragma once
#include <bits/stdc++.h>
#include <internal/battle/NormalPoint.hpp>
#include <internal/card/Card.hpp>

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class HeroPoint : public NormalPoint{
private:
    bool shootFlag = false;
    vector<short> level;
    vector<short> bomb;
    vector<Card> list;
    bool moveFlag = false;
    short stopShoot = 240;
    short shootpenalty = 0;

public:
    void shooting(bool flag);
    
    void moving(bool flag);

    void setCardlist(vector<Card> sets);

    void changeDirection(double per);

    short levelUp(short target);

    void timer(vector<BulletPoint> &bullets);

    void contact(pair<double, double> point, short large);

    void shoot(vector<BulletPoint> &bullets);

    short getBomb();
};