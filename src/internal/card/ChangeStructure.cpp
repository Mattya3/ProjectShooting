#include <internal/card/ChangeStructure.hpp>

using namespace std;
ChangeStructure::ChangeStructure(void) {
    CardHas has;
    hasAllCards = has.callCardLineup();
    StructureData sets;
    set3Cards = sets.callCardSets();
    // ChangeStructureView view(this);
}

vector<Card> ChangeStructure::callHasAllCards(){
    return hasAllCards;
}

vector<Card> ChangeStructure::callSet3Cards(){
    return set3Cards;
}

void ChangeStructure::ChangeStructureCard(short point, short id){
    short i;
    for(i = 0; i < hasAllCards.size(); i++)
        if(hasAllCards.at(i).id == id)
            break;
    this->set3Cards.at(point) = hasAllCards.at(i);
}

void ChangeStructure::registerNewCard(int id){
    CardHas has;
    has.writeHasCard(id);
}

void ChangeStructure::registerStructure(void){
    vector<short> no(3);
    for(int i = 0; i < 3; i++)
        no.at(i) = this->set3Cards.at(i).id;
    StructureData card;
    card.writeCardSets(no);
}
vector<int> ChangeStructure::get_having_card_id(){
    vector<int> ret;
    for(auto &&e : hasAllCards) ret.emplace_back(e.id);
    return ret;
}