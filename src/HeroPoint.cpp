#include <bits/stdc++.h>
#include "NormalPoint.cpp"
#include "../include/Card.hpp"

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class HeroPoint : public NormalPoint{
public:
    //int shootNum = 1;
    //int attack = 20;
    //int nowHP;
    //int maxHP;
    //pair<double, double> position;
    //int size;
    //int exp;
    //int vector;
    //int stopShoot;
    //int shootpenalty;
    //double angle = 0;//ラジアン表記, ただし0未満では停止する
    //BulletPoint bullet;
    vector<int> level;
    vector<Card> list;

    void setCardlist(vector<Card> sets){
        list = sets.copy();
        for(int i = 0; i < list.size(); i++){
            level.push_back(1);
            exp += list.at(i).needEXP;
        }
    }

    int levelUp(int target){
        int changedNum;
        list.at(target).upNum--;
        if(level.at(target)++ == 1) changedNum = list.at(target).uped1;
        else changedNum = list.at(target).uped2;
        if(list.at(target).typeA == 0){
            switch(list.at(target).typeA){
                case 0: 
                    vector = changedNum;
                    break;
                case 1: 
                    size = changedNum;
                    break;     
            }
        }else{
            switch(list.at(target).typeA){
                case 0: 
                    bullet.vector = changedNum;
                    break;
                case 1: 
                    bullet.size = changedNum;
                    break;
                case 2: 
                    bullet.attack = changedNum;
                    break;
                case 3: 
                    bullet.attack = changedNum;
                    break;
                case 4: 
                    bullet.canReflect = changedNum;
                    break;
                case 5:
                    shootNum = changedNum / 100;
                    shotAngle = changedNum % 100;
                    break;
                 case 6:
                    bullet.searchLange = (changedNum / 10) * 10;
                    bullet.hormingPower = (changedNum % 10) * 0.1;
                    break;
                case 7:
                    //ボムの記載、未作成

            }
        }
        return -exp;
    }

    void timer(){
        if(shootpenalty > 0) shootpenalty--;
        move();
    }

    //NormalPoint(int hp, int large, int get, int vec){
    //    nowHP = hp;
    //    maxHP = hp;
    //    size = large;
    //    exp = get;
    //    vector = vec;
    //}

    //void setFirstSituation(pair<double, double> z){
    //    position = z;
    //}

    //void changeAngle(double per){
    //    angle = per;
    //}

    //void setBulletData(vector<int> bullet){
    //    bulletID = bullet;
    //}

    //void move(){
    //    position.first += cos(angle);
    //    position.second -= sin(angle);   
    //}

    //bool damage(int hit){//ダメージ処理、HPが0以下ならtrueを返す
    //    nowHP -= hit;
    //    if(nowHP <= 0) return true;
    //    else return false;
    //}
};