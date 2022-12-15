#include <component/Location.hpp>
Location::Location(int sx, int sy, int xlen, int ylen) {
    double x = sx;
    double y = sy;
    Setting::to_canonical_xy(x, y);
    this->sx = x;
    this->sy = y;
    this->xlen = double(xlen) / double(Setting::WINDOW_width)*2;
    this->ylen = double(ylen) / double(Setting::WINDOW_height)*2;
}