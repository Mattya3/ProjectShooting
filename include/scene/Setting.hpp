#pragma once
#include <DataOf2D.hpp>
namespace sbfw {

class Setting {

  private:
  public:
    Setting() = default;
    int WINDOW_width = 800, WINDOW_height = 700;
    inline void to_canonical_xy(float &x, float &y) {
        x /= WINDOW_width / 2;
        y /= WINDOW_height / 2;
        y = 1 - y;
        x = x - 1;
    }
    inline void to_canonical_xy(double &x, double &y) {
        x /= WINDOW_width / 2;
        y /= WINDOW_height / 2;
        y = 1 - y;
        x = x - 1;
    }
};

} // namespace sbfw
