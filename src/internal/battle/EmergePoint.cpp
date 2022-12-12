#include <internal/battle/EmergePoint.hpp>

void EmergePoint::setFirst(string line){

}

void EmergePoint::putPattern(string line){
    
}

void wastePattern(){

}

vector<string> EmergePoint::split(string str, char separator){//strをseparatorで分割する関数
    vector<string> output;//帰り値用, 分割後の文字列のリスト
    stringstream getString(str);//分割後の一時保存用の変数
    string x;//分割後の一時保存用の変数
    while(getline(getString, x, separator)) output.push_back(x);
    return output;
}