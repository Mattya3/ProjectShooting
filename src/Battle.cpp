#include "../include/Battle.hpp"

void Battle::start(){
    StructureData sets;
    vector<Card> list = sets.callCardSets();
    hero.setSize(battle_height, battle_width);
    hero.setting(100, 64, 0, 10, 240);
    hero.setCardlist(list);
    hero.setHitTime = 1000;
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
    while(hero.nowHP > 0) timer();
}

void Battle::timer(){
    vector<pair<double, double>> points;
    vector<int> large;
    this_thread::sleep_for(chrono::milliseconds(20));
    /*
    for(int i = 0; i < enemy.size(); i++){
        enemy.at(i).timer();
        points.push_back(enemy.at(i).getPosition());
        large.push_back(enemy.at(i).getSize());
    }
    */
    hero.timer(points, large);
    collision();
}

void Battle::collision(){
    vector<int> dis;
    dis = hero.collision(hero.bullets);
    for(int i = 0; i < dis.size(); i++) hero.lostBullet(i);
    /*
    for(int j = 0; j < enemy.size(); j++){
        dis = hero.collision(enemy.at(j).bullets);
        for(int i = 0; i < dis.size(); i++) enemy.at(j).lostBullet(i);
    }
    for(int j = 0; j < enemy.size(); j++){
        dis = enemy.at(j).collision(hero.bullets);
        for(int i = 0; i < dis.size(); i++) hero.lostBullet(i);
    }
    */
   hero.notReflect();
   //for(int i = 0; i < enemy.size(); i++) enemy.at(i).notReflect();
   /*
   for(int i = enemy.size() - 1; i >= 0; i--){
    if(enemy.at(i).lose()) enemy.erase(enemy.begin() + i);
   } //倒されたかどうか
   */

   //for(int i = 0; i < enemy.size(); i++) hero.contact(enemy.at(i).getPosition, enemy.at(i).getSize);
}