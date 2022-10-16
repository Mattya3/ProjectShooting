// #include "../include/funcA.hpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
    string str;
    cin >> str;
    string s1,s2;
    s1=str;
    cout << "input :";
    for(auto &&e : s1) {
        if(e == '\\'){
            e='/';
        }
    }
    for (auto &&e : str)
    {
        if(e=='\\'){
            s2.append("\\\\");
        }else{
            s2.push_back(e);
        }
    }
    
    cout << endl;
    cout << s1 << "\n";
    cout << s2 << "\n";
    


    return 0;
}