#pragma once
#include <bits/stdc++.h>

#include <DataOf2D.hpp>
#include <sbfw.hpp>
#include <unit.hpp>
using namespace std;
namespace stgview {

/// @brief 残機やボム数を表示するための同一画像を複数設置するクラス
class RemainingStatus {
  private:
    sbfw::texture::DynamicUnit img;

    int object_num = 5;
    int now_stock, max_stock = 100;
    DataOf2D view_start_point;
    float interval = 0.02;

  public:
    void Draw(int now_stock);
    RemainingStatus(int object_num, DataOf2D drawstart,
                    pair<int, DataOf2D> id_len)
        : img(id_len.first, id_len.second), object_num(object_num),
          view_start_point(drawstart) {}
    RemainingStatus() {}
};
} // namespace stgview
