#pragma once
#include "DataOf2D.hpp"
#include <bits/stdc++.h>
#include <component/Location.hpp>
#include <setting.hpp>
using namespace std;
using pdd = pair<double, double>;

class CenterLocation {
  private:
    pdd get_Yboundary(); // X方向の範囲を返す
    pdd get_Xboundary(); // Y方向の範囲を返す
  public:
    DataOf2D c;   // 中心
    DataOf2D len; // 中心から端まで 画像サイズの半分
    // オブジェクト同士すなわち大きさを持つ同士がぶつかっているか判定
    static bool is_object_collision(CenterLocation s, CenterLocation t);
    void add(double cx, double cy);
    // ある点pが呼び出したインスタンスの内部にあるか否か
    bool is_in_square_pos(DataOf2D p);
    // CenterLocaionをLocationへ変換する
    Location to_Location() {
        return Location(c.x - len.x, c.y - len.y, len.x * 2, len.y * 2);
    }
    inline void set_cxy(DataOf2D x) { c = x; }
    inline void set_cxy(double x, double y) { c = DataOf2D(x, y); }

    inline void set_len(DataOf2D x) { len = x; }
    inline DataOf2D get_cxy() { return c; }
    inline DataOf2D get_len() { return len; }
    inline void dump() {
        cout << "cx=" << c.x << ", cy=" << c.y << ", lx=" << len.x
             << ", ly=" << len.y << endl;
    }
    inline CenterLocation get() { return CenterLocation(c, len); }
    inline double left() { return c.x - len.x; }
    inline double right() { return c.x + len.x; }
    inline double up() { return c.y + len.y; }
    inline double down() { return c.y - len.y; }
    // コンストラクタ
    CenterLocation();
    // Locationから
    CenterLocation(Location l);
    CenterLocation(DataOf2D d, DataOf2D f);
    CenterLocation(double cx, double cy, double lenx2, double leny2);

    ~CenterLocation();
};
