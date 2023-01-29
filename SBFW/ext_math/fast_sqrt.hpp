
namespace optm {
inline float fast_sqrt(const float &x) {
    float xHalf = 0.5f * x;
    int tmp = 0x5F3759DF - (*(int *)&x >> 1); // initial guess
    float xRes = *(float *)&tmp;
    xRes *= (1.5f - (xHalf * xRes * xRes));
    // xRes *= (1.5f - (xHalf * xRes * xRes));  // 精度up、計算時間2倍
    return xRes * x;
}
} // namespace optm
