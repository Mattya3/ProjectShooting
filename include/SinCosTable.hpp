#pragma once
#include <bits/stdc++.h>
using namespace std;
constexpr static float PI = 3.1415926536;
// 名前衝突を避けるために関数は sin=osin, cos=ocosで呼ぶ
// 全てfloatで実装 doubleで受け取る意味はない
class SinCosTable {
    // 3.14...を何分割するか
    int sz;
    int PI10;
    vector<float> _sin;

  public:
    // szを大きくすれば精度up 必要メモリ増
    // sz=500~3000くらいが良さげ

    SinCosTable(int sz) : sz(sz), PI10(sz * PI) {
        int N = PI10 + 1;
        _sin.resize(N);
        const float d = (1.0 / sz);
        float x = 0.0;
        for(int i = 0; i < N; i++, x += d) {
            _sin[i] = std::sin(x);
        }
    }
    inline float osin(float x) {
        x *= sz;
        int th = int(x);
        if(th > 2 * PI10) {
            th %= (2 * PI10);
        }
        if(0 <= th && th <= PI10) {
            return _sin[th];
        } else {
            return -_sin[th - PI10];
        }
    }
    inline float ocos(float x) { return osin(x + (M_PI / 2.0)); }
};