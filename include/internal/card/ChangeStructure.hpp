#pragma once
#include <bits/stdc++.h>
#include "StructureData.hpp"
#include "Card.hpp"

using namespace std;

class ChangeStructure{
private:
    vector<Card> list;
    vector<Card> hasCards;

public:
    ChangeStructure(void);

    void ChangeStructureCard(int point, Card data);

    void legisterStructure(void);
};