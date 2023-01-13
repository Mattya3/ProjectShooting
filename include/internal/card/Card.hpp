#pragma once
#include <bits/stdc++.h>
#include <internal/Split.hpp>
using namespace std;

class Card{//カードデータを保存する関数
public:
    string cardName;//カード名
    string cardExplain;//カード説明文
    short id;//識別用
    short typeA;//強化種類1(自機or弾)
    short typeB;//強化種類2()
    short needEXP;//必要経験量
    short upNum;//レベルアップ回数
    short uped1 = 0;//レベル2強化後数値
    short uped2 = 0;//レベル3強化後数値

    void putCardText(string line);

    void putCardData(short no, string line);
};
