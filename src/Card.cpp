#include <bits/stdc++.h>
using namespace std;

class Card{//カードデータを保存する関数
public:
    string cardName;
    string cardExplain;
    int typeA;
    int typeB;
    int needEXP;
    int upNum;
    int uped1 = 0;
    int uped2 = 0;

    vector<string> split(string str, char separator){
        vector<string> output;
        stringstream getString(str);
        string x;
        while(getline(getString, x, separator)) output.push_back(x);
        return output;
    }

    void putCardText(string line){
        vector<string> splitString = split(line, ' ');
        cardName = splitString.at(0);
        cardExplain = splitString.at(1);
    }

    void putCardData(string line){
        vector<string> splitString = split(line, ' ');
        typeA = stoi(splitString.at(0));
        typeB = stoi(splitString.at(1));
        needEXP = stoi(splitString.at(2));
        upNum = stoi(splitString.at(3));
        if(upNum > 0){
            uped1 = stoi(splitString.at(4));
            if(upNum > 1){
                uped1 = stoi(splitString.at(5));
            }
        }
    }
};
