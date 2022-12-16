#pragma once
#include <setting.hpp>
// pairでのfirst,secondのアクセスが長いから
// pair<double, double>でcompileのnoteがうるさいから
// 以上を防ぐため実装
#include <bits/stdc++.h>
class DataOf2D {
  private:
  public:
    double x, y;
    DataOf2D() {}
    DataOf2D(double x, double y) : x(x), y(y) {}
    // rationは画像の拡大率を表す
    DataOf2D(unsigned int ix, unsigned int iy, double ratio) {
        x = double(ix) / Setting::WINDOW_width * ratio;
        y = double(iy) / Setting::WINDOW_height * ratio;
    }
    ~DataOf2D() {}
    DataOf2D &operator+=(const DataOf2D rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    DataOf2D operator+(const DataOf2D rhs) { return *this += rhs; }
    DataOf2D &operator-=(const DataOf2D rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    DataOf2D operator-(const DataOf2D rhs) { return *this -= rhs; }
    DataOf2D operator*=(const int r) {
        x *= r;
        y *= r;
        return *this;
    }

    DataOf2D operator*(const int r) { return *this *= r; }

    void dump() { std::cout << x << ',' << y << std::endl; }
};
