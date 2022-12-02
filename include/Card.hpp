#include <bits/stdc++.h>
using namespace std;

class Card{//カードデータを保存する関数
public:
    string cardName;//カード名
    string cardExplain;//カード説明文
    int id;//識別用
    int typeA;//強化種類1(自機or弾)
    int typeB;//強化種類2()
    int needEXP;//必要経験量
    int upNum;//レベルアップ回数
    int uped1 = 0;//レベル2強化後数値
    int uped2 = 0;//レベル3強化後数値

    vector<string> split(string str, char separator);

    void putCardText(string line);

    void putCardData(int no, string line);
};
