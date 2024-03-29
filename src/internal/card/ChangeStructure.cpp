#include <internal/card/ChangeStructure.hpp>

using namespace std;
void ChangeStructure::setting() {//カード情報を保管するコンストラクタ
    CardHas has;
    hasAllCards = has.callCardLineup();
    StructureData sets;
    set3Cards = sets.callCardSets();
}

vector<Card> ChangeStructure::callHasAllCards(){//所持カードをvectorで返す関数
    CardHas has;
    hasAllCards = has.callCardLineup();
    return hasAllCards;
}

vector<Card> ChangeStructure::callSet3Cards(){//セットカードをvectorで返す関数
    StructureData sets;
    set3Cards = sets.callCardSets();
    return set3Cards;
}

void ChangeStructure::ChangeStructureCard(short point, short id){//セットカードを一カ所変更する関数
    short i;
    CardHas has;
    hasAllCards = has.callCardLineup();
    for(i = 0; i < hasAllCards.size(); i++) if(hasAllCards.at(i).id == id) break;//変更先カードの特定
    set3Cards.at(point) = hasAllCards.at(i);
}

void ChangeStructure::registerNewCard(int id){//新たな入手カードを反映する関数
    CardHas has;
    has.writeHasCard(id);
}

bool ChangeStructure::registerStructure(void){//セットカードを反映する関数
    vector<pair<short, short>> check(3);
    vector<short> no(3);
    for(short i = 0; i < 3; i++){
        no.at(i) = this->set3Cards.at(i).id;
        check.at(i).first = this->set3Cards.at(i).typeA;
        check.at(i).second = this->set3Cards.at(i).typeB;
    }
    for(short i = 0; i < 3; i++){
        if(check.at(i % 3) == check.at((i + 1) % 3) && (check.at(i % 3).first == 0 || check.at(i % 3).first == 1)) return false;
    }
    StructureData card;
    card.writeCardSets(no);
    return true;
}
vector<int> ChangeStructure::get_having_card_id(){//所持カードidを返す関数
    vector<int> ret;
    for(auto &&e : hasAllCards) ret.emplace_back(e.id);
    return ret;
}