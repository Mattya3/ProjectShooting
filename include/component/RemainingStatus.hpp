#pragma once
#include <DataOf2D.hpp>
#include <bits/stdc++.h>
#include <component/Image.hpp>
using namespace std;

class RemainingStatus {
  private:
    PngTexture valid_tex, invalid_tex;

    int now_stock = 3, max_stock = 3;
    DataOf2D view_start_point, len;

  public:
    void view() {
        DataOf2D p = view_start_point;
        for(int i = 1; i < max_stock + 1; i++) {
            if(i <= now_stock) {
                valid_tex.view(p);
            } else {
                invalid_tex.view(p);
            }
            p.x += len.x * 1.8;
        }
    }
    void view(int having_stoc) {
        DataOf2D p = view_start_point;
        for(int i = 1; i < max_stock + 1; i++) {
            if(i <= having_stoc) {
                valid_tex.view(p);
            } else {
                invalid_tex.view(p);
            }
            p.x += len.x * 1.8;
        }
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
