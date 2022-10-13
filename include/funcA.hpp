#include <bits/stdc++.h>
// #include <boost/range/algorithm.hpp>

class funcA {
  private:
    int val = 5;

  public:
    funcA();
    funcA(int x);
    ~funcA();
    inline void show() { std::cout << val << "\n"; }
    int calc(int add);
};
