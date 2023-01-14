#pragma once
#include <bits/stdc++.h>
#include <internal/battle/BulletPoint.hpp>
#include <internal/Split.hpp>
#include <filesystem>
using std::filesystem::current_path;
using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class NormalPoint{
public:
    short id;
    short height;
    short width;
    short shootNum;
    double shootAngle;
    short nowHP;
    short maxHP;
    pair<double, double> position;
    short size;
    short exp;
    double velocity;
    double nowVelocity;
    short setHitTime;
    short hitTime = 0;
    double angle;//ラジアン表記
    double direction;//ラジアン表記
    BulletPoint bullet;

    void setting(short id);

    void setFirstSituation(pair<double, double> z);

    short getExp();

    pair<double, double> getPosition();

    short getSize();

    double getAngle();

    void changeAngle(double per);

    double getDirection();

    void move();

    void damage(short hit);

    vector<short> collision(vector<BulletPoint> bullets, short range);

    void setBullet(short bulletId);

    bool alive();
};