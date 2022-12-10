#include "../include/EnemyPoint.hpp"

void EnemyPoint::getEnemyData(int id){
}

void EnemyPoint::timer(vector<pair<double, double>> points, vector<int> large){
    if(shootpenalty > 0) shootpenalty -= 20;
    if(hitTime > 0) hitTime -= 20;
    //move();
    if(/*弾を撃つ条件であれば*/false) shoot();
    for(int i = 0; i < bullets.size(); i++){
        bullets.at(i).timer(points,large);
    } 
}

void EnemyPoint::shoot(){
    int count = shootNum;
    double changeAngle = shootAngle * M_PI / 180;
    double afterAngle;
    cout << "shoot" << shootNum << endl;
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

void EnemyPoint::changeDirection(){

}

void EnemyPoint::setMovePattern(int id){

}

void EnemyPoint::setShootPattern(int id){
    
}