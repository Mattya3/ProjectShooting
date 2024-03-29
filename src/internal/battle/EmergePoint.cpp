#include <internal/battle/EmergePoint.hpp>

short EmergePoint::setFirst(string line){
    moving.clear();
    vector<string> data = split(line, ' ');
    emergeTime = stoi(data.at(0));
    enemyId = stoi(data.at(1));
    emergePosition.first = stod(data.at(3));
    emergePosition.second = stod(data.at(4));
    return stoi(data.at(2));
}

void EmergePoint::putPattern(string line){
    PatternPoint token;
    token.putPattern(line);
    moving.push_back(token);
}

short EmergePoint::comeTime(){
    return emergeTime;
}

short EmergePoint::comeEnemyId(){
    return enemyId;
}

pair<double, double> EmergePoint::comePosition(){
    return emergePosition;
}

vector<PatternPoint> EmergePoint::comeMovePattern(){
    return moving;
}