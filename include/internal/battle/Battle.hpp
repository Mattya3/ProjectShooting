#pragma once
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <internal/card/StructureData.hpp>
#include <internal/battle/HeroPoint.hpp>
#include <internal/battle/EnemyPoint.hpp>
#include <internal/battle/BulletPoint.hpp>
#include <internal/battle/EmergePoint.hpp>
#include <internal/battle/GamePointView.hpp>
using namespace std;

const int battle_height = 660;
const int battle_width = 440;

class Battle{
public:
    GamePointView viewer;
    vector<EmergePoint> appear;
    HeroPoint hero;
    vector<EnemyPoint> enemy;
    int score = 0;
    int time = 0;

    void start(int stage);

    void timer();

    void collision();

    void encount();

    void loading(int stage);

    void inputMoving(bool flag);

    void inputShooting(bool flag);

    void inputAngle(double angle);

    void inputLevelUp(int target);
};