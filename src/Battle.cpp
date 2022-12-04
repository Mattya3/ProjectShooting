#include "../include/Battle.hpp"

void Battle::start(){
    StructureData sets;
    vector<Card> list = sets.callCardSets();
    hero.setSize(battle_height, battle_width);
    hero.setting(100, 64, 0, 10, 240);
    hero.setCardlist(list);
    pair<double, double> z;
    z.first = battle_width / 2;
    z.second = 3 * battle_height / 4;
    hero.setFirstSituation(z);
    hero.changeAngle(M_PI / 2);
    BulletPoint b;
    hero.setBulletData(b);
    z.first = 100;
    z.second = 100;
    b.setSize(battle_height, battle_width);
    b.setFirstSituation(z);
    b.changeAngle(M_PI / 4);
    hero.bullets.push_back(b);
    hero.moveFlag = true; //後ほど削除する
    timer();
}

void Battle::timer(){
    while (true){
        this_thread::sleep_for(chrono::milliseconds(20));
        hero.timer();
        collision();
    }
}

void Battle::collision(){
}
