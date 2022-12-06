#include "../include/NormalPoint.hpp"

void NormalPoint::setSize(int h, int w){
    height = h;
    width = w;
}

void NormalPoint::setting(int hp, int large, int get, int vec, int stop){
    nowHP = hp;
    maxHP = hp;
    size = large;
    exp = get;
    velocity = vec;
    stopShoot = stop;
    shootpenalty = 0;
}

void NormalPoint::setFirstSituation(pair<double, double> z){
    position = z;
}

void NormalPoint::changeAngle(double per){
    angle = per;
}

void NormalPoint::setBulletData(BulletPoint bullets){
    bullet = bullets;
}

void NormalPoint::move(){
    if(moveFlag){
        position.first += velocity * cos(angle);
        position.first = max(position.first, (double)size / 2);
        position.first = min(position.first, (double)(width - 1) - (double)size / 2);
        position.second -= velocity * sin(angle);
        position.second = max(position.second, (double)size / 2);
        position.second = min(position.second, (double)(height - 1) - (double)size / 2);
        cout<<"hero" << nowHP <<  ":" <<position.first << "," << position.second << endl;
    }
}

bool NormalPoint::damage(int hit){ //ダメージ処理、HPが0以下ならtrueを返す
    nowHP -= hit;
    if (nowHP <= 0) return true;
    else return false;
}

void NormalPoint::shoot(){
    if (shootpenalty <= 0){
        cout << "shoot" << endl;
        pair<double, double> shooter;
        shooter.first = position.first + size * cos(angle) / 2;
        shooter.second = position.second - size * sin(angle) / 2;
        bullet.setSize(height, width);
        bullet.setFirstSituation(shooter);
        bullet.changeAngle(angle);
        bullets.push_back(bullet);
        shootpenalty = stopShoot;
    }
}

vector<int> NormalPoint::collision(vector<BulletPoint> bullets){
    vector<int> bulletId;
    int x, y, d, r;
    for(int i = 0; i < bullets.size(); i++){
        x = position.first - bullets.at(i).position.first;
        y = position.second - bullets.at(i).position.second;
        d = x * x + y * y;
        r = (size + bullets.at(i).size) / 2;
        r *= r;
        if(d <= r){
            cout << "hit!!" << endl;
            if(hitTime <= 0){
                damage(bullets.at(i).attack);
                hitTime = setHitTime;
            } 
            bulletId.push_back(i);
        }
    }
    return bulletId;
}

void NormalPoint::lostBullet(int id){
    bullets.erase(bullets.begin() + id);
}

void NormalPoint::notReflect(){
    for(int i = 0; i < bullets.size(); i++){
        if(bullets.at(i).velocity <= 0){
            bullets.erase(bullets.begin() + i);
            cout << "lost" << endl;
        } 
    }
}