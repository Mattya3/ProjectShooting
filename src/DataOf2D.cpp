#include <DataOf2D.hpp>

DataOf2D operator*(const float lhs, const DataOf2D &rhs) {
    return DataOf2D(lhs * rhs.x, lhs * rhs.y);
}

DataOf2D operator*(const DataOf2D &rhs, const float lhs) {
    return DataOf2D(lhs * rhs.x, lhs * rhs.y);
}