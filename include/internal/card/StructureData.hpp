#pragma once
#include <bits/stdc++.h>
#include <internal/card/Card.hpp>
#include <internal/card/CardHas.hpp>

using namespace std;

class StructureData{
public:
    vector<Card> callCardSets(void);

    vector<int> readCardSets(void);

    vector<string> split(string str, char separator);

    void writeCardSets(vector<int> list);
};