#include <bits/stdc++.h>

using namespace std;

#define M_PI 3.14159265358979323846264338327950288

class BulletPoint{
public:
    int attack;
    int nowHP = 20;
    int maxHP = 20;
    pair<double, double> position;
    int size = 32;
    int vector = 10;
    int canReflect = 1;
    double searchLange = 0;
    double hormingPower = 0;//従来の角度とホーミング方向の比率、1で完全追尾、0で性能0
    double angle = 0;//ラジアン表記, ただし0未満では停止する

    bool reflect(int wallID){//0-4で→↑←↓の壁に対応, 反射不可ならtrue
        if(--canReflect <= 0) return true;
        else{
            switch(wallID){
                case 0:
                    if(angle < M_PI){
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
                    if(angle < M_PI){
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

    void setFirstSituation(pair<double, double> z){
        position = z;
    }

    void changeAngle(double per){
        angle = per;
    }

    double search(){
        if(searchLange == 0 || hormingPower == 0) return -1;
        //索敵、当たり判定処理のように記述するので後ほど
    }

    void move(){
        double per = search();
        if(per >= 0){   
            position.first += cos(angle) * (1 - hormingPower) + cos(per) * hormingPower;
            position.second -= sin(angle) * (1 - hormingPower) + sin(per) * hormingPower;
            //範囲超え、未記載
        }else{
            position.first += cos(angle);
            position.second -= sin(angle); 
            //範囲超え、未記載
        } 
    }

    bool damage(int hit){//ダメージ処理、HPが0以下ならtrueを返す
        nowHP -= hit;
        if(nowHP <= 0) return true;
        else return false;
    }

    void timer(){
        move();
    }
};