#include "DataOf2D.hpp"

float DataOf2D::norm_pow2(DataOf2D const &p) {
    return (this->x - p.x) * (this->x - p.x) +
           (this->y - p.y) * (this->y - p.y);
}
float DataOf2D::norm_pow2() const {
    return this->x * this->x + this->y * this->y;
}

DataOf2D DataOf2D::rotate(float theta) const {
    auto r = optm::fast_sqrt(x * x + y * y);
    auto t = atan2f(y, x);
    return DataOf2D(r * cos(theta + t), r * sin(theta + t));
}
DataOf2D &DataOf2D::rotate_ref(float theta) {
    auto r = optm::fast_sqrt(x * x + y * y);
    auto t = atan2f(y, x);
    *this = DataOf2D(r * cos(theta + t), r * sin(theta + t));
    return *this;
}

DataOf2D DataOf2D::normalize(float scale) const {
    auto t = optm::fast_sqrt(x * x + y * y);
    return DataOf2D(*this * scale) / t;
}
DataOf2D &DataOf2D::normalize_ref(float scale) {
    auto t = optm::fast_sqrt(x * x + y * y);
    *this *= scale;
    return *this /= t;
}

DataOf2D operator*(const float lhs, const DataOf2D &rhs) {
    return DataOf2D(lhs * rhs.x, lhs * rhs.y);
}

DataOf2D DataOf2D::by_andgle_radius(float r, float theta) {
    return DataOf2D(r * cos(theta), r * sin(theta));
}