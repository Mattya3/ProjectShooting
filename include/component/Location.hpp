#pragma once

class Location {
  public:
    double sx, sy;
    double xlen, ylen;
    Location(double sx, double sy, double xlen, double ylen)
        : sx(sx), sy(sy), xlen(xlen), ylen(ylen) {}
    Location(){}
    // Location(Location c){}
};
