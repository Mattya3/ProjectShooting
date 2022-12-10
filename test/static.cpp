#include <bits/stdc++.h>
using namespace std;
class tes {
  public:
    static int x;
    void add() { ++x; }
};
int tes::x = 0;

int main() {
    tes t;
    tes::x = 0;
    cout << tes::x << endl;
    t.add();
    cout << tes::x << endl;
    cout << t.x << endl;

    return 0;
}