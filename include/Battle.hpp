#pragma once
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include "StructureData.hpp"
#include "HeroPoint.hpp"
#include "BulletPoint.hpp"
using namespace std;

const int battle_height = 660;
const int battle_width = 440;

class Battle{
public:
    HeroPoint hero;
    //vector<BulletPoint> enemyBullet;
    int score = 0;

    void start();

    void timer();

    void collision();
};