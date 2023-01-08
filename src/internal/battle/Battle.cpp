#include <filesystem>
#include <internal/battle/Battle.hpp>
#include <bits/stdc++.h>
using namespace std;

void Battle::start(int stage) {//初期設定用のメソッド, 引数はステージ番号
    StructureData sets;
    vector<Card> list = sets.callCardSets();
    hero.setting(0);
    hero.setBullet(0);
    hero.setCardlist(list);
    viewer.putCard(list);
    pair<double, double> z;
    z.first = battle_width / 2;
    z.second = 3 * battle_height / 4;
    hero.setFirstSituation(z);
    hero.changeDirection(M_PI / 2);
    loading(stage);
    // while(hero.nowHP > 0 && (appear.size() != 0 || enemy.size() != 0));
    // timer();
}

void Battle::timer() {//メイン動作用の変数、毎回呼び出す
    int heroBulletBeforeSize = heroBullets.size();
    vector<pair<double, double>> heroPoints;//自機座標
    vector<int> heroLarge;//自機サイズ
    vector<pair<double, double>> enemyPoints;//敵座標列
    vector<int> enemyLarge;//敵サイズ列
    this_thread::sleep_for(chrono::milliseconds(20));//毎回20ms待機することで50fpsを再現
    time += 20;
    heroPoints.push_back(hero.getPosition());
    heroLarge.push_back(hero.getSize());
    for(int i = 0; i < enemy.size(); i++) {//各敵を動作させる
        enemy.at(i).timer(heroPoints, enemyBullets);
        enemyPoints.push_back(enemy.at(i).getPosition());
        enemyLarge.push_back(enemy.at(i).getSize());
    }
    hero.timer(heroBullets);//自機を動作させる
    for(int i = 0; i < heroBullets.size(); i++) heroBullets.at(i).timer(enemyPoints, enemyLarge);
    for(int i = 0; i < enemyBullets.size(); i++) enemyBullets.at(i).timer(heroPoints, heroLarge);
    collision(heroBulletBeforeSize);
    do {//出現処理
        encount();
        if(appear.size() == 0)
            break;
    } while(appear.at(0).emergeTime == 0);//同時出現する敵がいなくなるまで
    viewer.putHero(hero, heroBullets);
    viewer.putEnemy(enemy, enemyBullets);
}

void Battle::collision(int size) {//接触判定のメソッド
    vector<int> dis;//ヒットした弾・敵がvectorのどこにいるかを保管
    dis = hero.collision(heroBullets, size);
    for(int i = 0; i < dis.size(); i++) heroBullets.erase(heroBullets.begin() + i);//自機とぶつかった自機の弾を消失
    dis = hero.collision(enemyBullets, enemyBullets.size());
    for(int i = 0; i < dis.size(); i++) enemyBullets.erase(enemyBullets.begin() + i);//自機とぶつかった敵の弾を消失
    for(int j = 0; j < enemy.size(); j++) {//敵とぶつかった際の上記の処理
        dis = enemy.at(j).collision(heroBullets, heroBullets.size());
        for(int i = 0; i < dis.size(); i++) heroBullets.erase(heroBullets.begin() + i);
    }
    for(int i = heroBullets.size() - 1; i >= 0; i--){//反射回数をオーバーした自機の弾を消失
        if(heroBullets.at(i).nonReflect()) heroBullets.erase(heroBullets.begin() + i);
    }
    for(int i = enemyBullets.size() - 1; i >= 0; i--){//反射回数をオーバーした敵の弾を消失
        if(enemyBullets.at(i).nonReflect()) enemyBullets.erase(enemyBullets.begin() + i);
    }
    for(int i = enemy.size() - 1; i >= 0; i--){
        hero.contact(enemy.at(i).getPosition(), enemy.at(i).getSize());//自機と敵がぶつかった際の処理
        if(!enemy.at(i).alive()){//敵のHP0による消失判定
            score += enemy.at(i).getExp();
            enemy.erase(enemy.begin() + i);
        }
    }
}

void Battle::encount() {//敵の出現処理メソッド
    if(appear.size() == 0) return;
    if((time >= appear.at(0).emergeTime && appear.at(0).emergeTime != -1) || (enemy.size() == 0 && appear.at(0).emergeTime == -1)) {//出現時間で全滅条件なし、または全滅条件ありで全滅済
        EnemyPoint emerge;
        emerge.setting(appear.at(0).enemyId);
        emerge.setFirstSituation(appear.at(0).emergePosition);
        emerge.setPattern(appear.at(0).moving);
        enemy.push_back(emerge);
        appear.erase(appear.begin());
        time = 0;//ファイル内の時間は1つ前からの経過時間であるので、タイマリセット
    }
}

void Battle::loading(int stage) {//ステージ読み込みのメソッド
    EmergePoint token;
    string line;
    int pattern;
    ifstream files((current_path() / filesystem::path("data/StageData/" + to_string(stage))).c_str()); // ファイル読み込み
    if(files.fail()) {
        cerr << "Error: not open StageData/" << stage
             << endl; // ファイル読み込みエラー発生時の処理
    }
    getline(files, line);//余分の読み込み
    getline(files, line);//余分の読み込み
    while(getline(files, line)) {//ファイル全体を読み込む
        pattern = token.setFirst(line);//各敵の動作パターンの数を入れる
        for(int i = 0; i < pattern; i++) {//動作パターンの数だけその敵に追加する
            getline(files, line);
            token.putPattern(line);
        }
        appear.push_back(token);
    }
}

void Battle::inputMoving(bool w, bool a, bool s ,bool d){//操作入力の反映メソッド
    if(w || a || s || d){//入力されているか
        double dx = 0, dy = 0;
        if(w) dy++;
        if(a) dx--;
        if(s) dy--;
        if(d) dx++;
        if(dx != 0 || dy != 0){//打ち消しされていないか
            hero.moving(true);
            dx /= sqrt(dx * dx + dy * dy);
            double per = acos(dx);
            if(dy < 0) per = 2 * M_PI - per;
            hero.changeDirection(per);
        }else{
            hero.moving(false);
        }
    }else{
        hero.moving(false);
    }
}

void Battle::inputShooting(bool flag){//操作入力の反映メソッド
    hero.shooting(flag);
}

void Battle::inputLevelUp(int target){//操作入力の反映メソッド
    if(score >= hero.getExp()){
        int up = hero.levelUp(target);
        if(up >= 0){
            score -= hero.getExp();
            viewer.putCardLevel(target, up);
        }
    }
}