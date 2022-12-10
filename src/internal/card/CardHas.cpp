
#include <bits/stdc++.h>
#include "CardHas.hpp"
using std::filesystem::current_path;
using namespace std;

vector<Card> CardHas::callCardLineup(void){//所持カードのリストをvectorで返す関数
    vector<bool> hasFlag = readHasCard();//所持しているかどうかをvectorで保持
    vector<Card> cards;//帰り値用, カードのリスト
    vector<string> splitString;//ファイル読み込み時の文字列を分割して入れる変数
    string line;//ファイル読み込み時の文字列をそのまま入れる変数
    Card nowCard;//代入用変数
    ifstream files((current_path() / filesystem::path("data/CardData")).c_str());//ファイル読み込み
    if(files.fail()){
        cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(files, line);
    for(int i = 0; i < hasFlag.size(); i++){//各カードに対してリストに入れるかのループ処理
        if(hasFlag.at(i)){//カードを所持している
            getline(files, line);
            nowCard.putCardText(line);//テキストデータを代入
            getline(files, line);
            nowCard.putCardData(i, line);//数値データを代入
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
        cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(files, line);
    puts = split(line, ' ');//putsに分割後を入れる
    for(int i = 0; i < puts.size(); i++){//各カードに対してフラグリストを作成するループ処理
        if(puts.at(i) == "0") output.push_back(false);//所持していないことを記入
        else output.push_back(true);//所持していることを記入
    }
    return output;
}

void CardHas::writeHasCard(int ID){
    string line1;//変更する所持カードリストの保持用
    string line2;//変更しないセットカードの保持用
    ifstream file1((current_path() / filesystem::path("data/SaveData")).c_str());//ファイル読み込み
    if(file1.fail()){
        cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(file1, line1);
    getline(file1, line2);
    vector<string> cards = split(line1, ' ');
    line1 = cards.at(0);
    for(int i = 1; i < cards.size(); i++){
        if(i == ID) line1 += " 1";
        else line1 = line1 + " " + cards.at(i);
    }
    ofstream file2((current_path() / filesystem::path("data/SaveData")).c_str(), ios::out);//ファイル読み込み
    if(file2.fail()){
        cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
    }
    file2 << line1 << endl;
    file2 << line2 << endl;
    file2.close();
}

vector<string> CardHas::split(string str, char separator){//strをseparatorで分割する関数
    vector<string> output;//帰り値用, 分割後の文字列のリスト
    stringstream getString(str);//分割後の一時保存用の変数
    string x;//分割後の一時保存用の変数
    while(getline(getString, x, separator)) output.push_back(x);
    return output;
}