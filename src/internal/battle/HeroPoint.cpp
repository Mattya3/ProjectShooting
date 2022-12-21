#include <internal/battle/HeroPoint.hpp>

void HeroPoint::shooting(bool flag){
    shootFlag = flag;
}
    
void HeroPoint::moving(bool flag){
    moveFlag = flag;
}

void HeroPoint::setCardlist(vector<Card> sets){
    list = sets;
    for (int i = 0; i < list.size(); i++){
        level.push_back(1);
        exp += list.at(i).needEXP;
    }
}

bool HeroPoint::levelUp(int target){
    int changedNum;
    if(list.at(target).upNum <= 0) return false;
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
    return true;
}

void HeroPoint::timer(vector<BulletPoint> &bullets){
    if(shootpenalty > 0) shootpenalty -= 20;
    if(hitTime > 0) hitTime -= 20;
    if(moveFlag) move();
    if(shootFlag) shoot(bullets);
}

void HeroPoint::contact(pair<double, double> point, int large){
    int x, y, d, r;
    x = position.first - point.first;
    y = position.second - point.second;
    d = x * x + y * y;
    r = (size + large) / 2;
    r *= r;
    if(d <= r){
        if(hitTime <= 0){
            damage(20);//ダメージ量確認
            hitTime = setHitTime;
        } 
    }
}

void HeroPoint::shoot(vector<BulletPoint> &bullets){
    if (shootpenalty <= 0){
        int count = shootNum;
        double changeAngle = shootAngle * M_PI / 180;
        double afterAngle;
        pair<double, double> shooter = position;
        shooter.first += size * cos(direction);
        shooter.second -= size * sin(direction);
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

void HeroPoint::changeDirection(double per){
    direction = per;
    changeAngle(per);
}