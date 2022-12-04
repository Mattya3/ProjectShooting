#include "../include/BulletPoint.hpp"

void BulletPoint::setSize(int h, int w){
    height = h;
    width = w;
}

bool BulletPoint::reflect(int wallID){ // 0-4で→↑←↓の壁に対応, 反射不可ならtrue
    if (--canReflect < 0) return false;
    else{
        switch (wallID){
            case 0:
                if (angle < M_PI){
                    angle = M_PI - angle;
                }else{
                    angle = 2 * M_PI - angle;
                    angle = M_PI + angle;
                }
                break;
            case 1:
                angle = 2 * M_PI - angle;
                break;
            case 2:
                if (angle < M_PI){
                    angle = M_PI - angle;
                }else{
                    angle = angle - M_PI;
                    angle = 2 * M_PI - angle;
                }
                break;
            case 3:
                angle = 2 * M_PI - angle;
                break;
        }
        return true;
    }
}

void BulletPoint::setFirstSituation(pair<double, double> z){
    position = z;
    cout << position.first << "," << position.second << endl;
}

void BulletPoint::changeAngle(double per){
    angle = per;
}

double BulletPoint::search(){
    if (searchLange == 0 || hormingPower == 0) return -1;
    //索敵、当たり判定処理のように記述するので後ほど
    return -1;//仮の戻り値
}

void BulletPoint::move(){
    double per = search();
    if (per >= 0) angle = acos(cos(angle) * (1 - hormingPower) + cos(per) * hormingPower);
    position.first += velocity * cos(angle);
    if(position.first < 0){
        if(reflect(2)) position.first = - position.first;
        else velocity = 0;//消滅判定、未作成
    }else if(position.first > width - 1){
        if(reflect(0)) position.first = 2 * width - position.first;
        else velocity = 0;//消滅判定、未作成 
    }
    position.second -= velocity * sin(angle);
    if(position.second < 0){
        if(reflect(1)) position.second = - position.second;
        else velocity = 0;//消滅判定、未作成
    }else if(position.second > height - 1){
        if(reflect(3)) position.second = 2 * height - position.second;
        else velocity = 0;//消滅判定、未作成 
    }
    cout << "bullet:" << angle << ":" << position.first << "," <<position.second << endl;
}

void BulletPoint::timer(){
    move();
}