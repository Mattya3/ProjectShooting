#include <bits/stdc++.h>
#include "StructureData.cpp"
using namespace std;

class ChangeStructure{
public:
    ChangeStructure(void){
        ChangeStructureView view();
    }    


    void legisterStructure(vector<int> list){
        StructureData card;
        card.writeCardSets(list);
    }
};