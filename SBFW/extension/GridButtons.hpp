#include <bits/stdc++.h>

#include "../sbfw.hpp"
#include "../unit.hpp"
namespace sbfw::ext {

void MakeGridButton(std::shared_ptr<sbfw::scene::SimpleScene> &scene,
                    DataOf2D draw_start_pos_upperleft, int width_num,
                    int height_num, float x_interval, float y_interval) {}

namespace detail {
struct FunctorForGridbtn {
    static int selected_idx;
    int idx;
    FunctorForGridbtn(int i) : idx(i) {}
    void operator()() { selected_idx = idx; }
};

void AllReset() {}
} // namespace detail
} // namespace sbfw::ext
