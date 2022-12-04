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
        position.first = max(position.first, (double)0);
        position.first = min(position.first, (double)(width - 1));
        position.second -= velocity * sin(angle);
        position.second = max(position.second, (double)0);
        position.second = min(position.second, (double)(height - 1));
        cout<<"hero:" <<position.first << "," << position.second << endl;
    }
}

bool NormalPoint::damage(int hit){ //ダメージ処理、HPが0以下ならtrueを返す
    nowHP -= hit;
    if (nowHP <= 0) return true;
    else return false;
}

void NormalPoint::shoot(){
    if (shootpenalty <= 0){
        //
    }
}
