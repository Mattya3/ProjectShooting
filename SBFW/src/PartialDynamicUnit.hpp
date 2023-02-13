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
    DataOf2D img_center_pos, partial_img_len;

    void view(DataOf2D p, float s = 1.0) {}

  public:
    void Draw(DataOf2D pos, float ratio);
    void Draw(DataOf2D pos);

  private:
    inline DataOf2D GetRegularLen(int w, int h) {
        return {w / float(window_width), h / float(window_height)};
    }
};
} // namespace sbfw::texture
