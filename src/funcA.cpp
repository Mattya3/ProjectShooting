#include "../include/funcA.hpp"
funcA::funcA() {}
funcA::funcA(int x): val(x) {}


funcA::~funcA() {}

int funcA::calc(int add) { return val + add; }