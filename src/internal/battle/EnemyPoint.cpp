#include <internal/battle/EnemyPoint.hpp>

void EnemyPoint::setPattern(vector<PatternPoint> move){
    moving = move;
    setBullet(moving.at(0).nowShootId());
}

void EnemyPoint::timer(vector<pair<double, double>> points, vector<BulletPoint> &bullets){
    if(hitTime > 0) hitTime -= 20;
    times += 20;
    if(moving.at(0).changeLine() > nowHP / maxHP){
        moving.erase(moving.begin());
        prepareMoving = true;
        directionFlag = true;
        movingUseStatus = 0;
        setBullet(moving.at(0).nowShootId());
    }
    if(moving.at(0).hasMoveId() != 1 && moving.at(0).maxLoopNum() <= moving.at(0).nowCountLoop()){
        moving.at(0).changeLoop();
        prepareMoving = true;
        directionFlag = true;
        movingUseStatus = 0;
        setBullet(moving.at(0).nowShootId());
    }
    makeMove();
    move();
    if(shootFlag) shoot(points.at(0), bullets);
}

void EnemyPoint::shoot(pair<double, double> points, vector<BulletPoint> &bullets){
    double random = M_PI *  moving.at(0).nowRandom() * (rand() % 100) / 18000;
    if(rand() % 2 == 1) random *= -1;
    int count = shootNum;
    double changeAngle = shootAngle * M_PI / 180;
    cout << shootAngle << ":" << changeAngle << endl;
    double afterAngle, forAngle;
    pair<double, double> shooter = position;
    bullet.setFirstSituation(shooter);
    if(moving.at(0).nowAngle() >= 0) forAngle = moving.at(0).nowAngle() + random;
    else forAngle = goHero(points) + random;
    if(forAngle < 0) forAngle += 2 * M_PI;
    if(forAngle > 2 * M_PI) forAngle -= 2 * M_PI;
    if(shootNum % 2 == 1){
        bullet.changeAngle(forAngle);
        bullets.push_back(bullet);
        count = (shootNum - 1) / 2;
        while(count > 0){
            afterAngle = forAngle + count * changeAngle;
            if(afterAngle < 0) afterAngle += 2 * M_PI;
            if(afterAngle > 2 * M_PI) afterAngle -= 2 * M_PI;
            bullet.changeAngle(afterAngle);
            bullets.push_back(bullet);
            afterAngle = forAngle - count * changeAngle;
            if(afterAngle < 0) afterAngle += 2 * M_PI;
            if(afterAngle > 2 * M_PI) afterAngle -= 2 * M_PI;
            bullet.changeAngle(afterAngle);
            bullets.push_back(bullet);
            count--;
        }
    }else{
        count = (shootNum - 1) / 2;
        while(count > 0){
            afterAngle = forAngle + (count + 1 / 2) * changeAngle;
            if(afterAngle < 0) afterAngle += 2 * M_PI;
            if(afterAngle > 2 * M_PI) afterAngle -= 2 * M_PI;
            bullet.changeAngle(afterAngle);
            bullets.push_back(bullet);
            afterAngle = forAngle - (count + 1 / 2) * changeAngle;
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
    switch (moving.at(0).nowMoveId()){
        case 0://静止(弾を300ms毎に発射)
            nowVelocity = 0;
            if(times >= 300){
                times = 0;
                shootFlag = true;
                moving.at(0).upLoop();
            }
            break;
        case 1://横(上)移動(弾を400ms毎に発射)
        case 2://横(下)移動(弾を400ms毎に発射)
            if(prepareMoving){
                nowVelocity = 0.5 * velocity;
                prepareMoving = goTo(-1, (4 * moving.at(0).nowMoveId() - 3) * height / 6, directionFlag);
                directionFlag = false;
            }else{
                nowVelocity = velocity;
                if(moving.at(0).nowCountLoop() % 2 == 0){
                    if(!goTo(size, -1, true)) moving.at(0).upLoop();
                }else{
                    if(!goTo(width - size, -1, true)) moving.at(0).upLoop();
                }
                if(times >= 400){
                    times = 0;
                    shootFlag = true;
                }
            }
            break;
        case 3://縦(左)移動(弾を400ms毎に発射)
        case 4://縦(右)移動(弾を400ms毎に発射)
            if(prepareMoving){
                nowVelocity = 0.5 * velocity;
                prepareMoving = goTo((3 * moving.at(0).nowMoveId() - 8) * width / 5,  -1, directionFlag);
                directionFlag = false;
            }else{
                nowVelocity = velocity;
                if(moving.at(0).nowCountLoop() % 2 == 0){
                    if(!goTo(-1, size, true)) moving.at(0).upLoop();
                }else{
                    if(!goTo(-1, height - size, true)) moving.at(0).upLoop();
                }
                if(times >= 400){
                    times = 0;
                    shootFlag = true;
                }
            }
            break;
        case 5://一発撃って消える(上から出てくる)
            if(prepareMoving){
                nowVelocity = 0.5 * velocity;
                prepareMoving = goTo(-1, height / 6, directionFlag);
                directionFlag = false;
                times = 0;
            }else{
                if(movingUseStatus == 1){
                    nowVelocity = 0.5 * velocity;
                    if(!goTo(-1, size, true)){
                        nowHP = 0;
                    }
                }else if(times >= 500 && movingUseStatus == 0){
                    movingUseStatus = 1;
                    shootFlag = true;
                }else{
                    nowVelocity = 0;
                }
            }        
            break;    
        case 6:
            if(prepareMoving){
                nowVelocity = 1.5 * velocity;
                prepareMoving = goTo(-1, height / 6, directionFlag);
                directionFlag = false;
                times = 0;
                movingUseStatus = 2;
            }else{
                if(movingUseStatus % 2 == 0){
                    nowVelocity = 2 * velocity;
                    if(!goTo((1 + 3 * movingUseStatus / 2) * width / 8, (2 - (movingUseStatus % 4) / 2) * height / 8, true)){
                        movingUseStatus++;
                        nowVelocity = 0;
                    }
                    times = 0;
                }else{
                    if(times >= 300){
                        movingUseStatus = (movingUseStatus + 1) % 6;
                        shootFlag = true;
                    }
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
    for(int i = 0; i < moving.at(0).nowShootId(); i++) getline(files, line);

}

bool EnemyPoint::goTo(short x, short y, bool flag){
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