#pragma once
#include <bits/stdc++.h>
using namespace std;

class GameCardMono{
public:
    string cardName;
    int cardLevel;
    int needEXP; //制限回数を超えたらここが-1になる
};