#include <internal/battle/PatternPoint.hpp>
    double changeHpLine;
    int hasPattern;
    int nowPattern;
    vector<int> moveId;
    vector<int> shootId;
    vector<int> loopNum;

    void PatternPoint::putPattern(string line){

    }

    void PatternPoint::changePattern(){

    }

vector<string> PatternPoint::split(string str, char separator){//strをseparatorで分割する関数
    vector<string> output;//帰り値用, 分割後の文字列のリスト
    stringstream getString(str);//分割後の一時保存用の変数
    string x;//分割後の一時保存用の変数
    while(getline(getString, x, separator)) output.push_back(x);
    return output;
}