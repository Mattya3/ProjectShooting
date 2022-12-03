#include <bits/stdc++.h>
using namespace std;
using std::filesystem::current_path;
int main() {
    cout << (current_path()/filesystem::path("img")).c_str()<<endl;
    return 0;
}