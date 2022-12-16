#include <internal/battle/PatternPoint.hpp>

void PatternPoint::putPattern(string line){
    vector<string> data = split(line, ' ');
    changeHpLine = stod(data.at(1));
    for(int i = 1; i <= stoi(data.at(2)); i++){
        moveId.push_back(stoi(data.at(3 * i)));
        shootId.push_back(stoi(data.at(3 * i + 1)));
        loopNum.push_back(stoi(data.at(3 * i + 2)));
    }
}

void PatternPoint::changeLoop(){
    nowLoop = 0;
    if(moveId.size() <= ++nowPattern) nowPattern = 0;
}

vector<string> PatternPoint::split(string str, char separator){//strをseparatorで分割する関数
    vector<string> output;//帰り値用, 分割後の文字列のリスト
    stringstream getString(str);//分割後の一時保存用の変数
    string x;//分割後の一時保存用の変数
    while(getline(getString, x, separator)) output.push_back(x);
    return output;
}