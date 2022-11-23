#include <bits/stdc++.h>
#include "Card.cpp"
using namespace std;

class CardHas{
public:
    vector<Card> callCardLineup(void){
        vector<bool> hasFlag = writeHasCard();
        vector<Card> cards;
        vector<string> splitString;
        Card nowCard;
        ifstream files("../data/CardData");
        if(files.fail()){
            cerr << "Error: not open file" << endl;
        }
        string line;
        getline(files, line);
        int cardNum = stoi(line);
        for(int i = 0; i < hasFlag.size(); i++){
            if(hasFlag.at(i)){
                getline(files, line);
                nowCard.putCardText(line);
                getline(files, line);
                nowCard.putCardData(line);
                cards.push_back(nowCard);
            }else{
                getline(files, line);
                getline(files, line);
            }
        }
        return cards;
    }

    vector<bool> writeHasCard(void){
        ifstream files("../data/SaveData");
        if(files.fail()){
            cerr << "Error: not open file" << endl;
        }
        string line;
        getline(files, line);
        vector<string> puts = split(line, ' ');
        vector<bool> output;
        for(int i = 0; i < puts.size(); i++){
            if(puts.at(i) == "0") output.push_back(false);
            else output.push_back(true);
        }
        return output;
    }

    vector<string> split(string str, char separator){
        vector<string> output;
        stringstream getString(str);
        string x;
        while(getline(getString, x, separator)) output.push_back(x);
        return output;
    }
};