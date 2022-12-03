#pragma once
#include <bits/stdc++.h>
#include "BulletPoint.hpp"

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class NormalPoint{
public:
    int shootNum = 1;
    double shotAngle = 0;
    int attack = 20;
    int nowHP;
    int maxHP;
    pair<double, double> position;
    int size;
    int exp;
    int velocity;
    int stopShoot;
    int shootpenalty;
    double angle = 0;//ラジアン表記, ただし0未満では停止する
    BulletPoint bullet;//未作成

    void setting(int hp, int large, int get, int vec, int stop);

    void setFirstSituation(pair<double, double> z);

    void changeAngle(double per);

    void setBulletData(BulletPoint bullets);

    void move();

    bool damage(int hit);

    void shoot();
};