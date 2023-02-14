#include <app_sbfw/Location.hpp>

Location::Location(int sx, int sy, int xlen, int ylen) {
    double x = sx;
    double y = sy + ylen;
    this->sx = x / double(Setting::WINDOW_width) * 2 - 1;
    this->sy = 1 - y / double(Setting::WINDOW_height) * 2;
    this->xlen = double(xlen) / double(Setting::WINDOW_width) * 2;
    this->ylen = double(ylen) / double(Setting::WINDOW_height) * 2;
}

