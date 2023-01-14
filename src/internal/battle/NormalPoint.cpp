#include <internal/battle/NormalPoint.hpp>

void NormalPoint::setting(short id){//初期設定用のメソッド
    vector<string> data;//ファイル読み取り
    string line;//
    ifstream files((current_path() / filesystem::path("data/PointData")).c_str());
    if(files.fail()){
        cerr << "Error: not open PointData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(files, line);
    data = split(line, ' ');
    height = stoi(data.at(0));
    width = stoi(data.at(1));
    bullet.setSize(height, width);
    for(int i = 0; i < id; i++) getline(files, line);
    getline(files, line);
    data = split(line, ' ');
    nowHP = stoi(data.at(0));
    maxHP = stoi(data.at(0));
    size = stoi(data.at(1));
    velocity = stoi(data.at(2));
    nowVelocity = stoi(data.at(2));
    setHitTime = stoi(data.at(3));
    exp = stoi(data.at(4));
    this->id = id;
}

void NormalPoint::setFirstSituation(pair<double, double> z){
    position = z;
}

void NormalPoint::changeAngle(double per){
    angle = per;
}

short NormalPoint::getExp(){
    return exp;
}

pair<double, double> NormalPoint::getPosition(){
    return position;
}

short NormalPoint::getSize(){
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
}

void NormalPoint::damage(short hit){ //ダメージ処理、HPが0以下ならtrueを返す
    nowHP -= hit;
}

vector<short> NormalPoint::collision(vector<BulletPoint> bullets, short range){
    vector<short> bulletId;
    double x, y, d, r;
    for(int i = 0; i < range; i++){
        x = position.first - bullets.at(i).getPosition(true);
        y = position.second - bullets.at(i).getPosition(false);
        d = sqrt(x * x + y * y);
        r = (size + bullets.at(i).getSize()) / 2;
        if(d < 0.7 * r){
            if(hitTime <= 0){
                damage(bullets.at(i).getDamage());
                hitTime = setHitTime;
            } 
            bulletId.push_back(i);
        }
    }
    return bulletId;
}

void NormalPoint::setBullet(short bulletId){
    string line;
    vector<string> data;
    ifstream files((current_path() / filesystem::path("data/BulletData")).c_str());//ファイル読み込み
    if(files.fail()){
        cerr << "Error: not open BulletData" << endl;//ファイル読み込みエラー発生時の処理
    }
    for(int i = 0; i < bulletId; i++) getline(files, line);
     getline(files, line);
    data = split(line, ' ');
    bullet.setting(data);
    shootNum = stoi(data.at(6));
    shootAngle = stod(data.at(7));
    angle = stod(data.at(8));
}

bool NormalPoint::alive(){
    if(nowHP > 0) return true;
    else return false;
}