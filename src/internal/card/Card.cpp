#include <internal/card/Card.hpp>

void Card::putCardText(string line){//テキストデータを保管する関数
    vector<string> splitString = split(line, ' ');//入力内容を分割
    cardName = splitString.at(0);
    cardExplain = splitString.at(1);
}

void Card::putCardData(short no, string line){//数値データを保管する関数
    id = no;
    vector<string> splitString = split(line, ' ');//入力内容を分割
    typeA = stoi(splitString.at(0));
    typeB = stoi(splitString.at(1));
    needEXP = stoi(splitString.at(2));
    upNum = stoi(splitString.at(3));
    if(upNum > 0){//レベルアップ回数が1回以上かどうか
        uped1 = stoi(splitString.at(4));
        if(upNum > 1){//レベルアップ回数が2回以上かどうか
            uped1 = stoi(splitString.at(5));
        }
    }
}