#pragma once
#include <bits/stdc++.h>
#include <internal/Split.hpp>
using namespace std;

class PatternPoint{//パターンデータを保存する関数
private:
    double changeHpLine;
    short nowPattern = 0;//現在どのmoveIdに対応しているか
    short nowLoop = 0;//同一のmoveIdが何回目なのか
    vector<short> moveId;
    vector<short> shootId;
    vector<short> loopNum; //何回loopする予定なのか
    vector<double> angles; //発射方向, -1で自機狙い
    vector<double> random; //弾のブレ

public:
    void putPattern(string line);

    void changeLoop();

    double changeLine();

    short nowShootId();

    short nowStatus();

    short nowMoveId();

    double nowAngle();

    double nowRandom();

    short maxLoopNum();

    void upStatus();//nowPatternの増加

    void upLoop();//nowLoopの増加

    short hasMoveId();

    short nowCountLoop();

};