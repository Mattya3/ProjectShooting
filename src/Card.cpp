#include <bits/stdc++.h>
using namespace std;

class Card{//カードデータを保存する関数
public:
    string cardName;//カード名
    string cardExplain;//カード説明文
    int typeA;//強化種類1(自機or弾)
    int typeB;//強化種類2()
    int needEXP;//必要経験量
    int upNum;//レベルアップ回数
    int uped1 = 0;//レベル2強化後数値
    int uped2 = 0;//レベル3強化後数値

    vector<string> split(string str, char separator){//strをseparatorで分割する関数
        vector<string> output;//帰り値用, 分割後の文字列のリスト
        stringstream getString(str);//分割後の一時保存用の変数
        string x;//分割後の一時保存用の変数
        while(getline(getString, x, separator)) output.push_back(x);
        return output;
    }

    void putCardText(string line){//テキストデータを保管する関数
        vector<string> splitString = split(line, ' ');//入力内容を分割
        cardName = splitString.at(0);
        cardExplain = splitString.at(1);
    }

    void putCardData(string line){//数値データを保管する関数
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
};
