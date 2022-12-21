#pragma once
// pairでのfirst,secondのアクセスが長いから
// 二次元座標を表す基本単位クラス
#include <Optimize/fast_sqrt.hpp>
#include <bits/stdc++.h>
#include <initializer_list>
#include <setting.hpp>
class DataOf2D {
  private:
  public:
    float x, y;
    DataOf2D() {}
    DataOf2D(float x, float y) : x(x), y(y) {}
    DataOf2D(std::initializer_list<float> init) {
        auto it = init.begin();
        x = *it;
        y = *(++it);
    }
    // rationは画像の拡大率を表す
    DataOf2D(unsigned int ix, unsigned int iy, double ratio) {
        x = double(ix) / Setting::WINDOW_width * ratio;
        y = double(iy) / Setting::WINDOW_height * ratio;
    }

    ~DataOf2D() {}
    DataOf2D normalize() {
        auto t = optm::fast_sqrt(x * x + y * y);
        x /= t;
        y /= t;
        return *this;
    }
    float dist2pow(DataOf2D const &p) {
        return (this->x - p.x) * (this->x - p.x) +
               (this->y - p.y) * (this->y - p.y);
    }
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
    DataOf2D &operator*=(const float rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    void dump() { std::cout << x << ',' << y << std::endl; }
    static DataOf2D to_viewpos_from_gamepos(DataOf2D x) {
        return DataOf2D(0, 0);
    }
};
DataOf2D operator*(const float lhs, const DataOf2D &rhs);

DataOf2D operator*(const DataOf2D &rhs, const float lhs);