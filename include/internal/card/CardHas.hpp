#pragma once
#include <bits/stdc++.h>
#include <internal/card/Card.hpp>
#include <internal/Split.hpp>
#include <filesystem>
using std::filesystem::current_path;
using namespace std;

class CardHas{
public:
    vector<Card> callCardLineup(void);

    vector<bool> readHasCard(void);

    void writeHasCard(short ID);

    string getCardName(short ID);

    vector<pair<string,bool>> getNewCard(int score); 
};