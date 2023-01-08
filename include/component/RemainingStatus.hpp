#pragma once
#include <DataOf2D.hpp>
#include <bits/stdc++.h>
#include <component/Image.hpp>
#include <component/simple_shapes.hpp>
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

class RemainingStatus {
  private:
    PngTexture valid_tex, invalid_tex;

    int heart_n = 5;
    int now_stock, max_stock;
    DataOf2D view_start_point, len;

  public:
    void view(int having_stoc) {
        float ratio = 1.8;
        DataOf2D p = view_start_point;
        float render_width = len.x * ratio * heart_n;
        for(int i = 1; i <= heart_n; i++) {
            valid_tex.view(p);
            p.x += len.x * ratio;
        }
        DataOf2D tm(view_start_point.x - len.x, view_start_point.y - len.y);
        Location l(tm.x + float(having_stoc) / float(max_stock) *
                              render_width,
                   tm.y,
                   float(max_stock - having_stoc) / float(max_stock) *
                       render_width,
                   len.y * ratio);
        filled_view___(l, 0, 1, 0);
    }
    RemainingStatus(DataOf2D st, PngTexture &valid, PngTexture &invalid,
                    int stock)
        : view_start_point(st), valid_tex(valid), invalid_tex(invalid),
          max_stock(stock), now_stock(stock) {
        len = DataOf2D(valid_tex.getWidth(), valid_tex.getHeight(), 1.0);
    }
    inline void decrement_stock() { now_stock = max(0, now_stock - 1); }
    inline void increment_stock() { now_stock = min(max_stock, now_stock + 1); }
    ~RemainingStatus() {}
};
