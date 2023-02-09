#include "math2D/DataOf2D.hpp"

namespace sbfw {
namespace texture {

class DynamicUnit {
  public:
    DataOf2D len;
    int this_id;

    DynamicUnit();
    DynamicUnit(int bind_id, DataOf2D len) : this_id(bind_id), len(len) {}
    void Draw(DataOf2D p) ;
    void Draw(DataOf2D p, float scale);

};

} // namespace texture

} // namespace sbfw
