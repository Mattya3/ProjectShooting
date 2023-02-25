#include <internal/card/CardHas.hpp>

vector<Card> CardHas::callCardLineup(void){//所持カードのリストをvectorで返す関数
    vector<bool> hasFlag = readHasCard();//所持しているかどうかをvectorで保持
    vector<Card> cards;//帰り値用, カードのリスト
    vector<string> splitString;//ファイル読み込み時の文字列を分割して入れる変数
    string line;//ファイル読み込み時の文字列をそのまま入れる変数
    Card nowCard;//代入用変数
    ifstream files((current_path() / filesystem::path("data/CardData")).c_str());//ファイル読み込み
    if(files.fail()){
        cerr << "Error: not open CardData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(files, line);
    for(int i = 0; i < hasFlag.size(); i++){//各カードに対してリストに入れるかのループ処理
        if(hasFlag.at(i)){//カードを所持している
            getline(files, line);
            nowCard.putCardText(line);
            getline(files, line);
            nowCard.putCardData(i, line);
            cards.push_back(nowCard);//カードをリストに入れる
        }else{//カードを所持していない
            getline(files, line);
            getline(files, line);
        }
    }
    return cards;
}

vector<bool> CardHas::readHasCard(void){//カードを所持しているかのフラグのリストをvectorで返す関数
    vector<bool> output;//帰り値用, カードフラグのリスト
    vector<string> puts;//ファイル読み込み時の文字列を分割して入れる変数
    string line;//ファイル読み込み時の文字列をそのまま入れる変数
    ifstream files((current_path() / filesystem::path("data/SaveData")).c_str());//ファイル読み込み
    if(files.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(files, line);
    puts = split(line, ' ');
    for(int i = 0; i < puts.size(); i++){//各カードに対してフラグリストを作成するループ処理
        if(puts.at(i) == "0") output.push_back(false);//所持していない
        else output.push_back(true);//所持している
    }
    return output;
}

void CardHas::writeHasCard(short ID){//所持カードをSaveDataに反映する関数
    string line1;//変更する所持カードリストの保持用
    string line2;//変更しないセットカードの保持用
    string line3;
    ifstream file1((current_path() / filesystem::path("data/SaveData")).c_str());//ファイル読み込み
    if(file1.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(file1, line1);
    getline(file1, line2);
    getline(file1, line3);
    vector<string> cards = split(line1, ' ');
    line1 = cards.at(0);
    for(int i = 1; i < cards.size(); i++){//全カードに対して所持状況を記録するループ処理
        if(i == ID) line1 += " 1";//所持している
        else line1 = line1 + " " + cards.at(i);//所持していない
    }
    ofstream file2((current_path() / filesystem::path("data/SaveData")).c_str(), ios::out);//ファイル読み込み
    if(file2.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    file2 << line1 << endl;
    file2 << line2 << endl;
    file2 << line3 << endl;
    file2.close();
}

string CardHas::getCardName(short ID){
    string line;
    ifstream file1((current_path() / filesystem::path("data/SaveData")).c_str());//ファイル読み込み
    if(file1.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(file1, line);
    for(short i = 0; i <= ID; i++) getline(file1, line);
    return split(line, ' ').at(0);
}

vector<pair<string, bool>> CardHas::getNewCard(short score){
    short cardNum;
    string token;
    vector<short> gets;
    vector<bool> has;
    vector<pair<string, bool>> output;
    pair<string, bool> point;
    ifstream files((current_path() / filesystem::path("data/CardData")).c_str());//ファイル読み込み
    if(files.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(files, token);
    cardNum = stoi(token);
    while(score > 0 && gets.size() < 7){
        gets.push_back(rand() % cardNum);
        score -= 500;
    }
    has = readHasCard();
    for(short i = 0; i < gets.size(); i++){
        point.first = getCardName(gets.at(i));
        point.second = has.at(gets.at(i));
        output.push_back(point);
    }
    return output;
}