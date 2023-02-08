#pragma once
#include "fast_sqrt.hpp"

#include <initializer_list>

class DataOf2D {
  public:
    float x, y;

  public:
    DataOf2D() = default;
    DataOf2D(float x, float y) : x(x), y(y) {}
    DataOf2D(std::initializer_list<float> init) {
        auto it = init.begin();
        x = *it;
        y = *(++it);
    }
    // 2つの座標から向きのベクトルを生成
    DataOf2D(DataOf2D const &from_pos, DataOf2D const &to_pos) {
        *this = to_pos - from_pos;
    }
    // 極座標指定でDataOf2Dを指定する
    // 動径と偏角から生成する
    static DataOf2D by_andgle_radius(float r, float theta);

    // ベクトルの大きさの二乗
    float norm_pow2(DataOf2D const &p);
    float norm_pow2() const;

    // 正規化する。大きさをscaleにする。デフォルトscale=1
    DataOf2D normalize(float scale = 1.0) const;
    DataOf2D &normalize_ref(float scale = 1.0);

    // 反時計回りにtheta分だけ回転
    DataOf2D rotate(float theta) const;
    DataOf2D &rotate_ref(float theta);
    // Location make_rect(DataOf2D sz);
    // Location make_rect(uint32_t w, uint32_t h);

    // 演算子オーバーロード
    DataOf2D &operator+=(const DataOf2D rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    DataOf2D &operator-=(const DataOf2D rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    // スカラーと二次元ベクトルの積
    DataOf2D &operator*=(const float rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    DataOf2D &operator/=(const float rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }
    DataOf2D operator+(const DataOf2D rhs) const {
        return DataOf2D(*this) += rhs;
    }
    DataOf2D operator-(const DataOf2D rhs) const {
        return DataOf2D(*this) -= rhs;
    }
    DataOf2D operator*(const float rhs) const { return DataOf2D(*this) *= rhs; }
    DataOf2D operator/(const float rhs) const { return DataOf2D(*this) /= rhs; }

    void dump();
};
// 左からの掛け算
DataOf2D operator*(const float lhs, const DataOf2D &rhs);
