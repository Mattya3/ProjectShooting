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

pair<double, double> NormalPoint::getPosition(){
    return position;
}

int NormalPoint::getSize(){
    return size;
}

double NormalPoint::getAngle(){
    return angle;
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
        int count = shootNum;
        double changeAngle = shootAngle * M_PI / 180;
        double afterAngle;
        cout << "shoot" << shootNum << endl;
        pair<double, double> shooter = position;
        shooter.first += size * cos(angle);
        shooter.second -= size * sin(angle);
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
        shootpenalty = stopShoot;
    }
}

vector<int> NormalPoint::collision(vector<BulletPoint> bullets){
    vector<int> bulletId;
    int x, y, d, r;
    for(int i = 0; i < bullets.size(); i++){
        x = position.first - bullets.at(i).position.first;
        y = position.second - bullets.at(i).position.second;
        d = sqrt(x * x + y * y);
        r = (size + bullets.at(i).size) / 2;
        d -= r;
        if(d < 0){
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