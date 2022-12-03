#include <bits/stdc++.h>
#include "BulletPoint.cpp"

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class NormalPoint{
public:
    int shootNum = 1;
    double shotAngle = 0;
    int attack = 20;
    int nowHP;
    int maxHP;
    pair<double, double> position;
    int size;
    int exp;
    int vector;
    int stopShoot;
    int shootpenalty;
    double angle = 0;//ラジアン表記, ただし0未満では停止する
    BulletPoint bullet;//未作成

    NormalPoint(int hp, int large, int get, int vec, int stop){
        nowHP = hp;
        maxHP = hp;
        size = large;
        exp = get;
        vector = vec;
        stopShoot = stop;
    }

    void setFirstSituation(pair<double, double> z){
        position = z;
    }

    void changeAngle(double per){
        angle = per;
    }

    void setBulletData(BulletPoint bullets){
        bullet = bullets;
    }

    void move(){
        position.first += cos(angle);
        //範囲超え、未記載
        position.second -= sin(angle); 
        //範囲超え、未記載  

    }

    bool damage(int hit){//ダメージ処理、HPが0以下ならtrueを返す
        nowHP -= hit;
        if(nowHP <= 0) return true;
        else return false;
    }

    void shoot(){
        if(shootpenalty <= 0){
            //弾の生成、未作成
        }
    }
};