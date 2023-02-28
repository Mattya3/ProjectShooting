#pragma once
#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <stgview/Combine.hpp>
#include <internal/BestScore.hpp>
#include <internal/card/StructureData.hpp>
#include <internal/battle/HeroPoint.hpp>
#include <internal/battle/EnemyPoint.hpp>
#include <internal/battle/BulletPoint.hpp>
#include <internal/battle/EmergePoint.hpp>
#include <internal/battle/GamePointView.hpp>
#include <filesystem>
using namespace std;

const short battle_height = 660;
const short battle_width = 440;

class Battle{
private:
    HeroPoint hero;
    vector<EnemyPoint> enemy;
    vector<BulletPoint> heroBullets;
    vector<BulletPoint> enemyBullets;
    vector<EmergePoint> appear;
    short score;
    int time;
    short clearLossTime;

public:
    GamePointView viewer;

    bool isContinue();

    void start(short stage);

    void timer();

    void collision(short size);

    void encount();

    void loading(short stage);

    void inputMoving(bool w, bool a, bool s, bool d);

    void inputShooting(bool flag);

    void inputLevelUp(short target);

    void inputBomb();

    void inputSpeed();
};