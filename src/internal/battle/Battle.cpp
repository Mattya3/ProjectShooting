#include <filesystem>
#include <internal/battle/Battle.hpp>
#include <bits/stdc++.h>
using namespace std;

void Battle::start(int stage) {
    StructureData sets;
    vector<Card> list = sets.callCardSets();
    hero.setting(0);
    hero.setBullet(0);
    hero.setCardlist(list);
    pair<double, double> z;
    z.first = battle_width / 2;
    z.second = 3 * battle_height / 4;
    hero.setFirstSituation(z);
    hero.changeDirection(M_PI / 2);
    loading(stage);
    // while(hero.nowHP > 0 && (appear.size() != 0 || enemy.size() != 0));
    // timer();
}

void Battle::timer() {
    vector<pair<double, double>> heroPoints;
    vector<int> heroLarge;
    vector<pair<double, double>> enemyPoints;
    vector<int> enemyLarge;
    this_thread::sleep_for(chrono::milliseconds(20));
    time += 20;
    heroPoints.push_back(hero.getPosition());
    heroLarge.push_back(hero.getSize());
    for(int i = 0; i < enemy.size(); i++) {
        enemy.at(i).timer(heroPoints, heroLarge);
        enemyPoints.push_back(enemy.at(i).getPosition());
        enemyLarge.push_back(enemy.at(i).getSize());
    }
    hero.timer(enemyPoints, enemyLarge);
    collision();
    do {
        encount();
        if(appear.size() == 0)
            break;
    } while(appear.at(0).emergeTime == 0);
    viewer.putHero(hero);
    viewer.putEnemy(enemy);
    cout << viewer.hero.position.first << "," << viewer.hero.position.second << endl;
}

void Battle::collision() {
    vector<int> dis;
    dis = hero.collision(hero.bullets);
    for(int i = 0; i < dis.size(); i++)
        hero.lostBullet(i);
    for(int j = 0; j < enemy.size(); j++) {
        dis = hero.collision(enemy.at(j).bullets);
        for(int i = 0; i < dis.size(); i++)
            enemy.at(j).lostBullet(i);
    }
    for(int j = 0; j < enemy.size(); j++) {
        dis = enemy.at(j).collision(hero.bullets);
        for(int i = 0; i < dis.size(); i++)
            hero.lostBullet(i);
    }
   hero.notReflect();
   for(int i = 0; i < enemy.size(); i++) enemy.at(i).notReflect();
   for(int i = enemy.size() - 1; i >= 0; i--){
    if(enemy.at(i).lose()) enemy.erase(enemy.begin() + i);
   }
   for(int i = 0; i < enemy.size(); i++) hero.contact(enemy.at(i).getPosition(), enemy.at(i).getSize());
}

void Battle::encount() {
    if(appear.size() == 0)
        return;
    if((time >= appear.at(0).emergeTime && appear.at(0).emergeTime != -1) ||
       (enemy.size() == 0 && appear.at(0).emergeTime == -1)) {
        EnemyPoint emerge;
        emerge.setting(appear.at(0).enemyId);
        emerge.setFirstSituation(appear.at(0).emergePosition);
        emerge.setPattern(appear.at(0).moving);
        enemy.push_back(emerge);
        appear.erase(appear.begin());
        time = 0;
    }
}

void Battle::loading(int stage) {
    EmergePoint token;
    string line;
    int pattern;
    ifstream files((current_path() /
                    filesystem::path("data/StageData/" + to_string(stage)))
                       .c_str()); // ファイル読み込み
    if(files.fail()) {
        cerr << "Error: not open StageData/" << stage
             << endl; // ファイル読み込みエラー発生時の処理
    }
    while(getline(files, line)) {
        pattern = token.setFirst(line);
        for(int i = 0; i < pattern; i++) {
            getline(files, line);
            token.putPattern(line);
        }
        appear.push_back(token);
    }
}

void Battle::inputMoving(bool w, bool a, bool s ,bool d){
    int l = 0, b=0, c=0, k=0;
    if(w) l++;
    if(a) b++;
    if(s) c++;
    if(d) k++;
    cout <<"w:"<<l<<" a:"<<b<<" s:"<<c<<"d:"<<k<<endl;
    if(w || a || s || d){
        double dx = 0, dy = 0;
        if(w) dy++;
        if(a) dx--;
        if(s) dy--;
        if(d) dx++;
        if(dx != 0 || dy != 0){
            hero.moving(true);
            dx /= sqrt(dx * dx + dy * dy);
            double per = acos(dx);
            if(dy < 0) per = 2 * M_PI - per;
            cout << "input angle:" << per << endl;
            hero.changeDirection(per);
        }else{
            hero.moving(false);
        }
    }else{
        hero.moving(false);
    }
}

void Battle::inputShooting(bool flag){
    hero.shooting(flag);
}

void Battle::inputLevelUp(int target){
    if(score >= hero.getExp()){
        if(hero.levelUp(target)) score -= hero.getExp();
    }
}