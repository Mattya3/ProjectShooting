#pragma once
#include <bits/stdc++.h>
#include <internal/battle/HeroPoint.hpp>
#include <internal/battle/EnemyPoint.hpp>
#include <internal/battle/BulletPoint.hpp>
#include <internal/battle/GamePointMono.hpp>
using namespace std;

class GamePointView{//カードデータを保存する関数
public:
    GamePointMono hero;
    vector<GamePointMono> enemies;
    vector<GamePointMono> heroBullets;
    vector<GamePointMono> enemyBullets;

    GamePointMono callHero();

    vector<GamePointMono> callEnemy();

    vector<GamePointMono> callHeroBullet();

    vector<GamePointMono> callEnemyBullet();

    void putHero(HeroPoint h);

    void putEnemy(vector<EnemyPoint> e);
};