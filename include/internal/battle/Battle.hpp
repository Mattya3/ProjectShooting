#pragma once
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <internal/card/StructureData.hpp>
#include <internal/battle/HeroPoint.hpp>
#include <internal/battle/EnemyPoint.hpp>
#include <internal/battle/BulletPoint.hpp>
using namespace std;

const int battle_height = 660;
const int battle_width = 440;

class Battle{
public:
    HeroPoint hero;
    vector<EnemyPoint> enemy;
    vector<BulletPoint> enemyBullet;
    int score = 0;

    void start();

    void timer();

    void collision();

    void encount();
};