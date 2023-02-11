#pragma once
#include "DynamicUnit.hpp"
#include "math2D/DataOf2D.hpp"
namespace sbfw {
extern int window_width, window_height;
} // namespace sbfw

namespace sbfw::texture {
class PartialDynamicUnit {
  public:
    PartialDynamicUnit() = default;
    PartialDynamicUnit(int sx, int sy, int w, int h,
                       std::tuple<int, DataOf2D, int, int>);

  public:
    DataOf2D len;
    int this_id;
    float tright, tdown, tup, tleft;

    void view(DataOf2D p, float s = 1.0) {}

  public:
    void Draw(DataOf2D pos, float ratio);
    void Draw(DataOf2D pos);

  private:
    inline DataOf2D GetRegularLen(int w, int h) {
        return {w / float(window_width) ,
                h / float(window_height)};
    }
    inline DataOf2D ToRegularXYpos(unsigned x, unsigned y) {
        float tx = x, ty = y;
        tx /= window_width / 2;
        ty /= window_height / 2;
        ty = 1 - ty;
        tx = tx - 1;
        return {tx, ty};
    }
    DataOf2D img_center_pos, partial_img_len;
};
} // namespace sbfw::texture
