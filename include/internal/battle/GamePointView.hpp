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
private:
    short heroHasHp;
    short exp;
    short needLevelUpEXP = 0;
    GamePointMono hero;
    vector<GamePointMono> enemies;
    vector<GamePointMono> heroBullets;
    vector<GamePointMono> enemyBullets;
    vector<GameCardMono> cards;

public:
    short callHp();

    short callNeedExp();//必要経験値　3枚のカードの上に表示
    
    short callExp();//所持経験値　HPの↓に表示

    GamePointMono callHero();

    vector<GamePointMono> callEnemy();

    vector<GamePointMono> callHeroBullet();

    vector<GamePointMono> callEnemyBullet();

    vector<GameCardMono> callCard();

    void putNeedExp(short need);

    void putExp(short get);

    void putHero(HeroPoint h, vector<BulletPoint> b);

    void putEnemy(vector<EnemyPoint> e, vector<BulletPoint> b);

    void putCard(vector<Card> l);

    void putCardLevel(short number, short count);
};