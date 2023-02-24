#pragma once
#include <bits/stdc++.h>
#include <internal/card/Card.hpp>
#include <internal/card/CardHas.hpp>
#include <filesystem>
#include <internal/Split.hpp>
using namespace std;
using std::filesystem::current_path;

class StructureData{
public:
    vector<Card> callCardSets(void);

    vector<short> readCardSets(void);

    void writeCardSets(vector<short> list);

    int StructureData::callBestScore();

    int StructureData::writeBestScore(int score);
};