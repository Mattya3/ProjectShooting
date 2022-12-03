#include <bits/stdc++.h>
#include "../include/StructureData.hpp"
#include "../include/HeroPoint.hpp"
#include "../include/BulletPoint.hpp"
using namespace std;

const int Battle_height = 660;
const int Battle_width = 440;

class Battle{
public:
    HeroPoint hero;
    vector<BulletPoint> heroBullet;
    vector<BulletPoint> enemyBullet;
    int score = 0;

    void start(){
        StructureData sets;
        vector<Card> list = sets.callCardSets();
        hero.setting(100, 64, 0, 10, 240);
        hero.setCardlist(list);
        pair<double, double> z;
        z.first = Battle_width / 2;
        z.second = 3 * Battle_height / 4;
        hero.setFirstSituation(z);
        hero.changeAngle(-1);
        BulletPoint b;
        hero.setBulletData(b);
    }

    void timer(){

    }
};