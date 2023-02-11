#pragma once
#include <DataOf2D.hpp>
#include <Image.hpp>
#include <bits/stdc++.h>
#include <sbfw.hpp>
#include <unit.hpp>
using namespace std;

static void filled_view___(Location l, float r, float g, float b) {
    glBegin(GL_POLYGON);
    glColor3d(r, g, b);
    glVertex2d(l.sx, l.sy);
    glVertex2d(l.sx + l.xlen, l.sy);
    glVertex2d(l.sx + l.xlen, l.sy + l.ylen);
    glVertex2d(l.sx, l.sy + l.ylen);
    glEnd();
}
/// @brief 残機やボム数を表示するための同一画像を複数設置するクラス
class RemainingStatus {
  private:
    PngTexture valid_tex, invalid_tex;
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
