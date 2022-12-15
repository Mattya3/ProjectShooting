#include <internal/battle/Battle.hpp>
#include <filesystem>

void Battle::start(int stage){
    StructureData sets;
    vector<Card> list = sets.callCardSets();
    hero.setting(0);
    hero.setCardlist(list);
    pair<double, double> z;
    z.first = battle_width / 2;
    z.second = 3 * battle_height / 4;
    hero.setFirstSituation(z);
    hero.changeDirection(0);
    loading(stage);
    while(hero.nowHP > 0 && (appear.size() != 0 || enemy.size() != 0)) timer();
}

void Battle::timer(){
    vector<pair<double, double>> points;
    vector<int> large;
    this_thread::sleep_for(chrono::milliseconds(20));
    time += 20;
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
    do{
        encount();
    }while(appear.at(0).emergeTime == 0);
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
    if((time <= appear.at(0).emergeTime && appear.at(0).emergeTime != -1) || (enemy.size() == 0 && appear.at(0).emergeTime == -1)){
        EnemyPoint emerge;
        emerge.setting(appear.at(0).enemyId);
        emerge.setFirstSituation(appear.at(0).emergePosition);
        emerge.setPattern(appear.at(0).moving);
        enemy.push_back(emerge);
        appear.erase(appear.begin());
        time = 0;
    }
}

void Battle::loading(int stage){
    EmergePoint token;
    string line;
    int pattern;
    ifstream files((current_path() / filesystem::path("data/StageData" + to_string(stage))).c_str());//ファイル読み込み
    if(files.fail()){
        cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
    }
    while(getline(files, line)){
        pattern = token.setFirst(line);
        for(int i = 0; i < pattern; i++){
            getline(files, line);
            token.putPattern(line);
        }
        appear.push_back(token);
    }
}