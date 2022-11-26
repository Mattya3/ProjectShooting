#include <bits/stdc++.h>
#include "StructureData.cpp"
#include "ChangeStructureView.cpp"

using namespace std;

class ChangeStructure{
private:
    vector<Card> list;
    vector<Card> hasCards;

public:
    ChangeStructure(void){
        CardHas has;
        list = has.callCardLineup();
        StructureData sets;
        hasCards = sets.callCardSets();
        ChangeStructureView view(this);
    }


    void legisterStructure(void){
        vector<int> no(3);
        for(int i = 0; i < 3; i++) no.at(i) = this->list.at(i).id;
        StructureData card;
        card.writeCardSets(no);
    }
};