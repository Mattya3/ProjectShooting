#include <funcA.hpp>

using namespace std;


int main(){
    funcA ins1;
    funcA ins2(8);
    ins1.show();
    ins1.calc(3);
    ins1.show();
    ins2.show();
    return 0;
}