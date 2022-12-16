#pragma once
#include <bits/stdc++.h>
#include <internal/card/Card.hpp>
#include <filesystem>
using std::filesystem::current_path;
using namespace std;

class CardHas{
public:
    vector<Card> callCardLineup(void);

    vector<bool> readHasCard(void);

    void writeHasCard(int ID);

    vector<string> split(string str, char separator);
};