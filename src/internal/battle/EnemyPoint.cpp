#include <internal/battle/EnemyPoint.hpp>

void EnemyPoint::setPattern(vector<PatternPoint> move){
    moving = move;
    setBullet(moving.at(0).shootId.at(0));
}

void EnemyPoint::timer(vector<pair<double, double>> points, vector<int> large){
    if(hitTime > 0) hitTime -= 20;
    times += 20;
    if(moving.at(0).changeHpLine > nowHP / maxHP){
        moving.erase(moving.begin());
        prepareMoving = true;
        movingUseStatus = 0;
        setBullet(moving.at(0).shootId.at(0));
    }
    if(moving.at(0).loopNum.at(moving.at(0).nowPattern) <= moving.at(0).nowLoop){
        moving.at(0).changeLoop();
        prepareMoving = true;
        movingUseStatus = 0;
        setBullet(moving.at(0).shootId.at(moving.at(0).nowPattern));
    }
    makeMove();
    move();
    if(shootFlag) shoot();
    for(int i = 0; i < bullets.size(); i++){
        bullets.at(i).timer(points,large);
    } 
}

void EnemyPoint::shoot(){
    int count = shootNum;
    double changeAngle = shootAngle * M_PI / 180;
    double afterAngle;
    pair<double, double> shooter = position;
    bullet.setSize(height, width);
    bullet.setFirstSituation(shooter);
    if(shootNum % 2 == 1){
        bullet.changeAngle(angle);
        bullets.push_back(bullet);
        count = (shootNum - 1) / 2;
        while(count > 0){
            afterAngle = angle + count * changeAngle;
            if(afterAngle < 0) afterAngle += 2 * M_PI;
            if(afterAngle > 2 * M_PI) afterAngle -= 2 * M_PI;
            bullet.changeAngle(afterAngle);
            bullets.push_back(bullet);
            afterAngle = angle - count * changeAngle;
            if(afterAngle < 0) afterAngle += 2 * M_PI;
            if(afterAngle > 2 * M_PI) afterAngle -= 2 * M_PI;
            bullet.changeAngle(afterAngle);
            bullets.push_back(bullet);
            count--;
        }
    }else{
        count = (shootNum - 1) / 2;
        while(count > 0){
            afterAngle = angle + (count + 1 / 2) * changeAngle;
            if(afterAngle < 0) afterAngle += 2 * M_PI;
            if(afterAngle > 2 * M_PI) afterAngle -= 2 * M_PI;
            bullet.changeAngle(afterAngle);
            bullets.push_back(bullet);
            afterAngle = angle - (count + 1 / 2) * changeAngle;
            if(afterAngle < 0) afterAngle += 2 * M_PI;
            if(afterAngle > 2 * M_PI) afterAngle -= 2 * M_PI;
            bullet.changeAngle(afterAngle);
            bullets.push_back(bullet);
            count--;
        }
    }
}

bool EnemyPoint::lose(){
    if(nowHP > 0) return false;
    else return true;
}


void EnemyPoint::makeMove(){

}

void EnemyPoint::changeBullet(){
    string line;
    ifstream files((current_path() / filesystem::path("data/BulletData")).c_str());//ファイル読み込み
    if(files.fail()){
        cerr << "Error: not open BulletData" << endl;//ファイル読み込みエラー発生時の処理
    }
    for(int i = 0; i < moving.at(0).shootId.at(moving.at(0).nowLoop); i++) getline(files, line);

}