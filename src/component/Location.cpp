#include <component/Location.hpp>
Location::Location(int sx, int sy, int xlen, int ylen) {
    double x = sx;
    double y = sy + ylen;
    this->sx = x / double(Setting::WINDOW_width) * 2 - 1;
    this->sy = 1 - y / double(Setting::WINDOW_height) * 2;
    this->xlen = double(xlen) / double(Setting::WINDOW_width) * 2;
    this->ylen = double(ylen) / double(Setting::WINDOW_height) * 2;
}
Location to_Location(GamePointMono gpm, int w, int h) {
    return Location(int(gpm.position.first), int(gpm.position.second), w, h);
}