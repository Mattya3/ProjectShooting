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
#include <filesystem>
using namespace std;

const int battle_height = 660;
const int battle_width = 440;

class Battle{
public:
    HeroPoint hero;
    vector<EnemyPoint> enemy;
    vector<BulletPoint> heroBullets;
    vector<BulletPoint> enemyBullets;
    GamePointView viewer;
    vector<EmergePoint> appear;
    int score = 0;
    int time = 0;

    void start(int stage);

    void timer();

    void collision(int size);

    void encount();

    void loading(int stage);

    void inputMoving(bool w, bool a, bool s, bool d);

    void inputShooting(bool flag);

    void inputLevelUp(int target);
};