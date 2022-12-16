#pragma once
#include <bits/stdc++.h>
#include <internal/card/Card.hpp>
#include <internal/card/StructureData.hpp>

using namespace std;

class ChangeStructure {
  private:
    vector<Card> hasAllCards;
    vector<Card> set3Cards;

  public:
    ChangeStructure(void);

    vector<Card> callHasAllCards();

    vector<Card> callSet3Cards();

    void ChangeStructureCard(int point, int id);

    void registerNewCard(int id);

    void registerStructure(void);

    vector<int> get_having_card_id();
};