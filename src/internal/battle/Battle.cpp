#include <internal/battle/Battle.hpp>

void Battle::start(){
    StructureData sets;
    vector<Card> list = sets.callCardSets();
    hero.setting(0);
    hero.setCardlist(list);
    pair<double, double> z;
    z.first = battle_width / 2;
    z.second = 3 * battle_height / 4;
    hero.setFirstSituation(z);
    hero.changeDirection(0);
    
    EnemyPoint emerge;//不要
    emerge.setting(0);//不要
    z.first = 200;//不要
    z.second = 200;//不要
    emerge.setFirstSituation(z);//不要
    enemy.push_back(emerge);//不要
    BulletPoint b;//不要
    b.setSize(battle_height, battle_width);//不要
    b.setFirstSituation(z);//不要
    b.changeAngle(0);//不要
    b.hormingPower = 1;//不要
    b.searchLange = 500;//不要
    enemy.at(0).bullets.push_back(b);//不要
    while(hero.nowHP > 0) timer();
}

void Battle::timer(){
    vector<pair<double, double>> points;
    vector<int> large;
    this_thread::sleep_for(chrono::milliseconds(20));
    for(int i = 0; i < enemy.size(); i++){
        points.push_back(hero.getPosition());
        large.push_back(hero.getSize());
        enemy.at(i).timer(points, large);
        points.erase(points.begin());
        large.erase(large.begin());
        points.push_back(enemy.at(i).getPosition());
        large.push_back(enemy.at(i).getSize());
    }
    hero.timer(points, large);
    collision();
    encount();
    cout << endl;//不要
}

void Battle::collision(){
    vector<int> dis;
    dis = hero.collision(hero.bullets);
    for(int i = 0; i < dis.size(); i++) hero.lostBullet(i);
    for(int j = 0; j < enemy.size(); j++){
        dis = hero.collision(enemy.at(j).bullets);
        for(int i = 0; i < dis.size(); i++) enemy.at(j).lostBullet(i);
    }
    for(int j = 0; j < enemy.size(); j++){
        dis = enemy.at(j).collision(hero.bullets);
        for(int i = 0; i < dis.size(); i++) hero.lostBullet(i);
    }
   hero.notReflect();
   for(int i = 0; i < enemy.size(); i++) enemy.at(i).notReflect();
   for(int i = enemy.size() - 1; i >= 0; i--){
    if(enemy.at(i).lose()) enemy.erase(enemy.begin() + i);
   }
   for(int i = 0; i < enemy.size(); i++) hero.contact(enemy.at(i).getPosition(), enemy.at(i).getSize());
}

void Battle::encount(){
    if(/*敵が出現する条件を満たしたら*/false){
        EnemyPoint emerge;
        emerge.setting(0);//引数は条件により変更
        pair<double, double> z;//ここに出現位置を代入する処理を加えたい
        z.first = 200;//不要
        z.second = 200;//不要
        emerge.setFirstSituation(z);
        enemy.push_back(emerge);
    }
}