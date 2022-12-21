#include <internal/battle/EnemyPoint.hpp>

void EnemyPoint::setPattern(vector<PatternPoint> move){
    moving = move;
    setBullet(moving.at(0).shootId.at(0));
}

void EnemyPoint::timer(vector<pair<double, double>> points, vector<BulletPoint> &bullets){
    if(hitTime > 0) hitTime -= 20;
    times += 20;
    if(moving.at(0).changeHpLine > nowHP / maxHP){
        moving.erase(moving.begin());
        prepareMoving = true;
        directionFlag = true;
        movingUseStatus = 0;
        setBullet(moving.at(0).shootId.at(0));
    }
    if(moving.at(0).moveId.size() != 0 && moving.at(0).loopNum.at(moving.at(0).nowPattern) <= moving.at(0).nowLoop){
        moving.at(0).changeLoop();
        prepareMoving = true;
        directionFlag = true;
        movingUseStatus = 0;
        setBullet(moving.at(0).shootId.at(moving.at(0).nowPattern));
    }
    makeMove();
    move();
    if(shootFlag) shoot(points.at(0), bullets);
}

void EnemyPoint::shoot(pair<double, double> points, vector<BulletPoint> &bullets){
    double random = moving.at(0).random.at(moving.at(0).nowLoop) * (rand() % 100);
    if(rand() % 2 == 1) random *= -1;
    int count = shootNum;
    double changeAngle = shootAngle * M_PI / 180;
    double afterAngle;
    pair<double, double> shooter = position;
    bullet.setFirstSituation(shooter);
    if(moving.at(0).angles.at(moving.at(0).nowLoop) >= 0) bullet.changeAngle(moving.at(0).angles.at(moving.at(0).nowLoop) + random);
    else bullet.changeAngle(goHero(points) + random);
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
    shootFlag = false;
}

bool EnemyPoint::lose(){
    if(nowHP > 0) return false;
    else return true;
}


void EnemyPoint::makeMove(){
    switch (moving.at(0).moveId.at(moving.at(0).nowPattern)){
        case 0://静止(弾を300ms毎に発射)
            nowVelocity = 0;
            if(times >= 300){
                times = 0;
                shootFlag = true;
            }
            break;
        case 1://横移動(弾を300ms毎に発射)
            if(prepareMoving){
                nowVelocity = 0.5 * velocity;
                prepareMoving = goTo(-1, height / 4, directionFlag);
                directionFlag = false;
            }else{
                nowVelocity = velocity;
                if(moving.at(0).nowLoop % 2 == 0){
                    if(!goTo(size, -1, directionFlag)){
                        moving.at(0).nowLoop++;
                        directionFlag = false;
                    }else{
                        directionFlag = true;
                    }
                }else{
                    if(!goTo(width - size, -1, directionFlag)){
                        moving.at(0).nowLoop++;
                        directionFlag = false;
                    }else{
                        directionFlag = true;
                    }
                }
                if(times >= 300){
                    times = 0;
                    shootFlag = true;
                }
            }
            break;
    
        default:
            break;
    }
}

void EnemyPoint::changeDirection(double per){
    direction = per;
}

void EnemyPoint::changeBullet(){
    string line;
    ifstream files((current_path() / filesystem::path("data/BulletData")).c_str());//ファイル読み込み
    if(files.fail()){
        cerr << "Error: not open BulletData" << endl;//ファイル読み込みエラー発生時の処理
    }
    for(int i = 0; i < moving.at(0).shootId.at(moving.at(0).nowLoop); i++) getline(files, line);

}

bool EnemyPoint::goTo(int x, int y, bool flag){
    if(x < 0){
        if(position.second == y) return false;
        if(position.second < y){
            changeDirection(3 * M_PI / 2);
            if(y - position.second < nowVelocity) nowVelocity = y - position.second;
        }
        else{
            changeDirection(M_PI / 2);
            if(position.second - y < nowVelocity) nowVelocity = position.second - y;
        } 
    }else if(y < 0){
        if(position.first == x) return false;
        if(position.first < x){
            changeDirection(0);
            if(x - position.first < nowVelocity) nowVelocity = x - position.first;
        }
        else{
            changeDirection(M_PI);
            if(position.first - x < nowVelocity) nowVelocity = position.first - x;
        } 
    }else{
        if(position.first == x && position.second == y) return false;
        if(flag){
            double dx = x - position.first;
            double dy = y - position.second;
            double r = sqrt(dx * dx + dy * dy);
            if(r < nowVelocity) nowVelocity = r;
            dx /= r;
            double directions = acos(dx);
            if(dy > 0) directions = 2 * M_PI - directions;
            changeDirection(directions);
        }
    }
    return true;
}

double EnemyPoint::goHero(pair<double, double> points){
    double dx = points.first - position.first;
    double dy = points.second - position.second;
    dx /= sqrt(dx * dx + dy * dy);
    double per = acos(dx);
    if(dy > 0) per = 2 * M_PI - per;
    return per;
}