#include <DataOf2D.hpp>

namespace sbfw{

class ElemInfo {
  public:
    ElemInfo(DataOf2D pos, std::string fname) : pos(pos), img_fname(fname),scale(1.0f) {}
    ElemInfo(DataOf2D pos, std::string fname, float scale) : pos(pos), img_fname(fname),scale(scale) {}

    const DataOf2D pos;
    const std::string img_fname;
    const float scale;
};

} // namespace sbfw
