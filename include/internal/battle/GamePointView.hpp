#pragma once
#include <bits/stdc++.h>
#include <internal/battle/HeroPoint.hpp>
#include <internal/battle/EnemyPoint.hpp>
#include <internal/battle/BulletPoint.hpp>
#include <internal/battle/GamePointMono.hpp>
#include <internal/battle/GameCardMono.hpp>
#include <internal/card/Card.hpp>

using namespace std;

class GamePointView{//カードデータを保存する関数
public:
    int herohasHp;
    GamePointMono hero;
    vector<GamePointMono> enemies;
    vector<GamePointMono> heroBullets;
    vector<GamePointMono> enemyBullets;
    vector<GameCardMono> cards;

    int callHp();

    GamePointMono callHero();

    vector<GamePointMono> callEnemy();

    vector<GamePointMono> callHeroBullet();

    vector<GamePointMono> callEnemyBullet();

    vector<GameCardMono> callCard();

    void putHp(int hp);

    void putHero(HeroPoint h, vector<BulletPoint> b);

    void putEnemy(vector<EnemyPoint> e, vector<BulletPoint> b);

    void putCard(vector<Card> l);

    void putCardLevel(int number, int count);
};