#pragma once
#include <bits/stdc++.h>

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class BulletPoint{
private:
    short height;
    short width;
    short attack;
    pair<double, double> position;
    short size;
    short velocity;
    short canReflect;
    double searchLange;
    double hormingPower;//従来の角度とホーミング方向の比率、1で完全追尾、0で性能0
    double angle = 0;//ラジアン表記

public:
    void setting(vector<string> data);

    void setSize(short h, short w);

    bool reflect(short wallID);

    void setFirstSituation(pair<double, double> z);

    void changeAngle(double per);

    double search(vector<pair<double, double>> points, vector<short> large);

    void move(vector<pair<double, double>> points, vector<short> large);

    void timer(vector<pair<double, double>> points, vector<short> large);

    bool nonReflect();

    pair<double, double> get2Position();

    double getPosition(bool isX);

    short getSize();

    short getDamage();

    void changeVelocity(short changed);

    void changeSize(short changed);

    void changeDamage(short changed);

    void changeReflect(short changed);

    void changeSearch(double changed);

    void changeHorming(double changed);
};