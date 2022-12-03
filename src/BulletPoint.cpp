#include "../include/BulletPoint.hpp"

bool BulletPoint::reflect(int wallID){ // 0-4で→↑←↓の壁に対応, 反射不可ならtrue
    if (--canReflect <= 0) return true;
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
        return false;
    }
}

void BulletPoint::setFirstSituation(pair<double, double> z){
    position = z;
}

void BulletPoint::changeAngle(double per){
    angle = per;
}

double BulletPoint::search(){
    if (searchLange == 0 || hormingPower == 0) return -1;
    //索敵、当たり判定処理のように記述するので後ほど
    return 0;//仮の戻り値
}

void BulletPoint::move(){
    double per = search();
    if (per >= 0) angle = acos(cos(angle) * (1 - hormingPower) + cos(per) * hormingPower);
    position.first += cos(angle);
    position.second -= sin(angle);
        //範囲超え、未記載
}

void BulletPoint::timer(){
    move();
}