#pragma once
#include <DataOf2D.hpp>

namespace sbfw {

class ElemInfo {
  public:
    ElemInfo() = default;
    ElemInfo(DataOf2D pos, std::string fname)
        : pos(pos), img_fname(fname), scale(1.0f) {}
    ElemInfo(DataOf2D pos, std::string fname, float scale)
        : pos(pos), img_fname(fname), scale(scale) {}

    DataOf2D pos;
    std::string img_fname;
    float scale;
};

} // namespace sbfw
