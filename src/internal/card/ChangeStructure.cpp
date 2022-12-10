#include <bits/stdc++.h>
#include "ChangeStructure.hpp"

using namespace std;
ChangeStructure::ChangeStructure(void){
    CardHas has;
    list = has.callCardLineup();
    StructureData sets;
    hasCards = sets.callCardSets();
    //ChangeStructureView view(this);
}

void ChangeStructure::ChangeStructureCard(int point, Card data){
    this->list.at(point) = data;
}

void ChangeStructure::legisterStructure(void){
    vector<int> no(3);
    for(int i = 0; i < 3; i++) no.at(i) = this->list.at(i).id;
    StructureData card;
    card.writeCardSets(no);
}