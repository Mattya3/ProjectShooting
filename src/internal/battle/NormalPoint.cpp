#include "NormalPoint.hpp"


void NormalPoint::setting(int id){
    vector<string> data;
    string line;
    ifstream files((current_path() / filesystem::path("data/PointData")).c_str());
    if(files.fail()){
        cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(files, line);
    data = split(line, ' ');
    height = stoi(data.at(0));
    width = stoi(data.at(1));
    for(int i = 0; i < id; i++) getline(files, line);
    getline(files, line);
    data = split(line, ' ');
    nowHP = stoi(data.at(0));
    maxHP = stoi(data.at(0));
    attack = stoi(data.at(1));
    size = stoi(data.at(2));
    velocity = stoi(data.at(3));
    nowVelocity = stoi(data.at(3));
    stopShoot = stoi(data.at(4));
    setHitTime = stoi(data.at(5));
    shootNum = stoi(data.at(6));
    shootAngle = stod(data.at(7));
    exp = stoi(data.at(8));
}

vector<string> NormalPoint::split(string str, char separator){//strをseparatorで分割する関数
    vector<string> output;//帰り値用, 分割後の文字列のリスト
    stringstream getString(str);//分割後の一時保存用の変数
    string x;//分割後の一時保存用の変数
    while(getline(getString, x, separator)) output.push_back(x);
    return output;
}

void NormalPoint::setFirstSituation(pair<double, double> z){
    position = z;
}

void NormalPoint::changeAngle(double per){
    angle = per;
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

double NormalPoint::getDirection(){
    return direction;
}

void NormalPoint::move(){
    position.first += nowVelocity * cos(direction);
    position.first = max(position.first, (double)size / 2);
    position.first = min(position.first, (double)(width - 1) - (double)size / 2);
    position.second -= nowVelocity * sin(direction);
    position.second = max(position.second, (double)size / 2);
    position.second = min(position.second, (double)(height - 1) - (double)size / 2);
    cout<<"moving" << nowHP <<  ":" <<position.first << "," << position.second << endl;
}

bool NormalPoint::damage(int hit){ //ダメージ処理、HPが0以下ならtrueを返す
    nowHP -= hit;
    if (nowHP <= 0) return true;
    else return false;
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