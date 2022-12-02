#include <bits/stdc++.h>
using namespace std;

int main() {
    int x = 0, y = 0;
    thread t([&] {
        for(int i = 0; i < 10; i++) {
            ++x;
        }
    });
    --y;
    cout << x << ", " << y << endl;
    t.join();
    return 0;
}
