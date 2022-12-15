#pragma once
#include <bits/stdc++.h>
#include <internal/battle/BulletPoint.hpp>
#include <filesystem>

using std::filesystem::current_path;

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class NormalPoint{
public:
    vector<BulletPoint> bullets;
    int id;
    int height;
    int width;
    int shootNum;
    double shootAngle;
    int attack;
    int nowHP;
    int maxHP;
    pair<double, double> position;
    int size;
    int exp;
    int velocity;
    int nowVelocity;
    int setHitTime;
    int hitTime = 0;
    double angle;//ラジアン表記
    double direction;//ラジアン表記
    BulletPoint bullet;

    void setting(int id);

    vector<string> split(string str, char separator);

    void setFirstSituation(pair<double, double> z);

    pair<double, double> getPosition();

    int getSize();

    double getAngle();

    void changeAngle(double per);

    double getDirection();

    void move();

    bool damage(int hit);

    vector<int> collision(vector<BulletPoint> bullets);

    void lostBullet(int Id);

    void notReflect();
};