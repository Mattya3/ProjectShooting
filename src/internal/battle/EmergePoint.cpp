#include <internal/battle/EmergePoint.hpp>

int EmergePoint::setFirst(string line){
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

vector<string> EmergePoint::split(string str, char separator){//strをseparatorで分割する関数
    vector<string> output;//帰り値用, 分割後の文字列のリスト
    stringstream getString(str);//分割後の一時保存用の変数
    string x;//分割後の一時保存用の変数
    while(getline(getString, x, separator)) output.push_back(x);
    return output;
}