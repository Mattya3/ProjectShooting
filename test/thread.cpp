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
    bool is_break = false;
    thread tt([&] {
        this_thread::sleep_for(chrono::milliseconds(2000));
        is_break = true;
    });

    while(true) {
        if(is_break) {
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(10));
    }   

    return 0;
}
