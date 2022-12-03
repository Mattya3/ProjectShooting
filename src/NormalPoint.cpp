#include "../include/NormalPoint.hpp"

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
    position.first += velocity * cos(angle);
    //範囲超え、未記載
    position.second -= velocity * sin(angle);
    //範囲超え、未記載
}

bool NormalPoint::damage(int hit){ //ダメージ処理、HPが0以下ならtrueを返す
    nowHP -= hit;
    if (nowHP <= 0) return true;
    else return false;
}

void NormalPoint::shoot(){
    if (shootpenalty <= 0){
        //弾の生成、未作成
    }
}
