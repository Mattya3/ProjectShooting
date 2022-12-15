#pragma once
#include <setting.hpp>
class Location {
  public:
    double sx, sy;
    double xlen, ylen;
    Location clone() { return Location(sx, sy, xlen, ylen); }
    Location(double sx, double sy, double xlen, double ylen)
        : sx(sx), sy(sy), xlen(xlen), ylen(ylen) {}
    Location(int sx, int sy, int xlen, int ylen);
    Location() {}
    // Location(Location &c):Location(c.sx,c.sy,c.xlen,c.ylen) {}
};
