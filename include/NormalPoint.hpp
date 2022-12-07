#pragma once
#include <bits/stdc++.h>
#include "BulletPoint.hpp"

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class NormalPoint{
public:
    vector<BulletPoint> bullets;
    int height;
    int width;
    bool moveFlag = false;
    int shootNum = 1;
    double shootAngle = 0;
    int attack = 20;
    int nowHP;
    int maxHP;
    pair<double, double> position;
    int size;
    int exp;
    int velocity;
    int stopShoot;
    int shootpenalty;
    int setHitTime = 20;
    int hitTime = 0;
    double angle = 0;//ラジアン表記, ただし0未満では停止する
    BulletPoint bullet;//未作成

    void setSize(int h, int w);

    void setting(int hp, int large, int get, int vec, int stop);

    void setFirstSituation(pair<double, double> z);

    pair<double, double> getPosition();

    int getSize();

    double getAngle();

    void changeAngle(double per);

    void setBulletData(BulletPoint bullets);

    void move();

    bool damage(int hit);

    void shoot();

    vector<int> collision(vector<BulletPoint> bullets);

    void lostBullet(int Id);

    void notReflect();
};