#pragma once
#include <bits/stdc++.h>
#include "Card.hpp"
#include "CardHas.hpp"

using namespace std;

class StructureData{
public:
    vector<Card> callCardSets(void);

    vector<int> readCardSets(void);

    vector<string> split(string str, char separator);

    void writeCardSets(vector<int> list);
};