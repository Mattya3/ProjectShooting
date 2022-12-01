#include <bits/stdc++.h>
#include "Card.hpp"
using namespace std;

class CardHas{
public:
    vector<Card> callCardLineup(void);

    vector<bool> readHasCard(void);

    void writeHasCard(int ID);

    vector<string> split(string str, char separator);
};