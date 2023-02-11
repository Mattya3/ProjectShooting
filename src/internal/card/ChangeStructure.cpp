#include <internal/card/ChangeStructure.hpp>

using namespace std;
ChangeStructure::ChangeStructure(void) {//カード情報を保管するコンストラクタ
    CardHas has;
    hasAllCards = has.callCardLineup();
    StructureData sets;
    set3Cards = sets.callCardSets();
}

vector<Card> ChangeStructure::callHasAllCards(){//所持カードをvectorで返す関数
    return hasAllCards;
}

vector<Card> ChangeStructure::callSet3Cards(){//セットカードをvectorで返す関数
    return set3Cards;
}

void ChangeStructure::ChangeStructureCard(short point, short id){//セットカードを一カ所変更する関数
    short i;
    for(i = 0; i < hasAllCards.size(); i++) if(hasAllCards.at(i).id == id) break;//変更先カードの特定
    set3Cards.at(point) = hasAllCards.at(i);
}

void ChangeStructure::registerNewCard(int id){//新たな入手カードを反映する関数
    CardHas has;
    has.writeHasCard(id);
}

void ChangeStructure::registerStructure(void){//セットカードを反映する関数
    vector<short> no(3);
    for(int i = 0; i < 3; i++)
        no.at(i) = this->set3Cards.at(i).id;
    StructureData card;
    card.writeCardSets(no);
}
vector<int> ChangeStructure::get_having_card_id(){//所持カードidを返す関数
    vector<int> ret;
    for(auto &&e : hasAllCards) ret.emplace_back(e.id);
    return ret;
}