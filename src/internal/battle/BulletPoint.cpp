#include <internal/battle/BulletPoint.hpp>

void BulletPoint::setting(vector<string> data){
    attack = stoi(data.at(0));
    size = stoi(data.at(1));
    velocity = stod(data.at(2));
    canReflect = stoi(data.at(3));
    searchLange = stod(data.at(4));
    hormingPower = stoi(data.at(5));
}

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
}

void BulletPoint::changeAngle(double per){
    angle = per;
}

double BulletPoint::search(vector<pair<double, double>> points, vector<int> large){
    if (searchLange == 0 || hormingPower == 0) return -1;
    double x, y, d;
    bool flag = true;
    double minx = 0, miny = 0, mind = searchLange;
    for(int i = 0; i < points.size(); i++){
        x = points.at(i).first - position.first;
        y = points.at(i).second - position.second;
        d = sqrt(x * x + y * y);
        if(d  < mind){
            flag = false;
            mind = d;
            minx = x;
            miny = y;
        }
    }
    if(flag) return -1;
    minx /= mind;
    double angle = acos(minx);
    if(miny > 0) angle = 2 * M_PI - angle;
    return angle;
}

void BulletPoint::move(vector<pair<double, double>> points, vector<int> large){//接触を内部にしているが、縁に移すかは未定
    double x, y, d;
    double per = search(points, large);
    if(per >= 0){
        x = cos(angle) * (1 - hormingPower) + cos(per) * hormingPower;
        y = sin(angle) * (1 - hormingPower) + sin(per) * hormingPower;
        d = sqrt(x * x + y * y);
        x /= d;
        angle = acos(x);
        if(y < 0) angle = 2 * M_PI - angle;
    }
    position.first += velocity * cos(angle);
    if(position.first < 0){
        if(reflect(2)) position.first = - position.first;
        else velocity = 0;
    }else if(position.first > width - 1){
        if(reflect(0)) position.first = 2 * width - position.first;
        else velocity = 0; 
    }
    position.second -= velocity * sin(angle);
    if(position.second < 0){
        if(reflect(1)) position.second = - position.second;
        else velocity = 0;
    }else if(position.second > height - 1){
        if(reflect(3)) position.second = 2 * height - position.second;
        else velocity = 0;
    }
}

void BulletPoint::timer(vector<pair<double, double>> points, vector<int> large){
    move(points, large);
}