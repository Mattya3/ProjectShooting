#include <bits/stdc++.h>
using namespace std;

class smart_ptrs {
  private:
    /* data */
    vector<unique_ptr<int>> _ve;

  public:
  // 引数は参照渡しでないといけない=コピーコンストラクタが呼べない
  // 
    void add(unique_ptr<int> &u) {
        assert(u != nullptr);
        _ve.emplace_back(move(u));
    }
    void show() {
        for(auto &&e : _ve) {
            cout << *e << endl;
        }
    }

    smart_ptrs(/* args */) {}
    ~smart_ptrs() {}
};

int main() {
    vector<unique_ptr<int>> ve;
    auto x = make_unique<int>(8);
    cout << *x << endl;
    ve.push_back(move(x));
    assert(x == nullptr);

    cout << *ve[0] << endl;
    auto y = make_unique<int>(99);
    smart_ptrs u;
    u.add(y);
    assert(y == nullptr);
    cout << "ok" << endl;
    u.show();
    return 0;
}