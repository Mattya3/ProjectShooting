#pragma once
#include <bits/stdc++.h>

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class BulletPoint{
public:
    int height;
    int width;
    int attack = 20;
    pair<double, double> position;
    int size = 32;
    int velocity = 30;
    int canReflect = 1;
    double searchLange = 0;
    double hormingPower = 0;//従来の角度とホーミング方向の比率、1で完全追尾、0で性能0
    double angle = 0;//ラジアン表記

    void setSize(int h, int w);

    bool reflect(int wallID);

    void setFirstSituation(pair<double, double> z);

    void changeAngle(double per);

    double search(vector<pair<double, double>> points, vector<int> large);

    void move(vector<pair<double, double>> points, vector<int> large);

    void timer(vector<pair<double, double>> points, vector<int> large);
};