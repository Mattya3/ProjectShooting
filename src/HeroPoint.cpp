#include "../include/HeroPoint.hpp"

void HeroPoint::setCardlist(vector<Card> sets){
    list = sets;
    for (int i = 0; i < list.size(); i++){
        level.push_back(1);
        exp += list.at(i).needEXP;
    }
}

int HeroPoint::levelUp(int target){
    int changedNum;
    list.at(target).upNum--;
    if (level.at(target)++ == 1) changedNum = list.at(target).uped1;
    else changedNum = list.at(target).uped2;
    if (list.at(target).typeA == 0){
        switch (list.at(target).typeA){
            case 0:
                velocity = changedNum;
                break;
            case 1:
                size = changedNum;
                break;
        }
    }else{
        switch (list.at(target).typeA){
            case 0:
                bullet.velocity = changedNum;
                break;
            case 1:
                bullet.size = changedNum;
                break;
            case 2:
                bullet.attack = changedNum;
                break;
            case 3:
                bullet.canReflect = changedNum;
                break;
            case 4:
                stopShoot = changedNum;
                break;
            case 5:
                shootNum = changedNum / 100;
                shootAngle = changedNum % 100;
                break;
            case 6:
                bullet.searchLange = (changedNum / 10) * 10;
                bullet.hormingPower = (changedNum % 10) * 0.1;
                break;
            case 7:
                //ボムの記載、未作成
                break;
        }
    }
    return -exp;
}

void HeroPoint::timer(vector<pair<double, double>> points, vector<int> large){
    if(shootpenalty > 0) shootpenalty -= 20;
    if(hitTime > 0) hitTime -= 20;
    move();
    if(shootFlag) shoot();
    for(int i = 0; i < bullets.size(); i++) bullets.at(i).timer(points,large);
}

void HeroPoint::contact(pair<double, double> point, int large){
    int x, y, d, r;
    x = position.first - point.first;
    y = position.second - point.second;
    d = x * x + y * y;
    r = (size + large) / 2;
    r *= r;
    if(d <= r){
        cout << "hit!!" << endl;
        if(hitTime <= 0){
            damage(20);
            hitTime = setHitTime;
        } 
    }
}
