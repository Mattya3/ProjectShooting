#include <bits/stdc++.h>
#include "Card.cpp"
using namespace std;

class CardHas{
public:
    vector<Card> callCardLineup(void){//所持カードのリストをvectorで返す関数
        vector<bool> hasFlag = writeHasCard();//所持しているかどうかをvectorで保持
        vector<Card> cards;//帰り値用, カードのリスト
        vector<string> splitString;//ファイル読み込み時の文字列を分割して入れる変数
        string line;//ファイル読み込み時の文字列をそのまま入れる変数
        Card nowCard;//代入用変数
        ifstream files("../data/CardData");//ファイル読み込み
        if(files.fail()){
            cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
        }
        getline(files, line);
        int cardNum = stoi(line);//カード数を代入
        for(int i = 0; i < hasFlag.size(); i++){//各カードに対してリストに入れるかのループ処理
            if(hasFlag.at(i)){//カードを所持している
                getline(files, line);
                nowCard.putCardText(line);//テキストデータを代入
                getline(files, line);
                nowCard.putCardData(line);//数値データを代入
                cards.push_back(nowCard);//カードをリストに入れる
            }else{//カードを所持していない
                getline(files, line);
                getline(files, line);
            }
        }
        return cards;
    }

    vector<Card> callCardSets(void){//セットカードのリストをvectorで返す関数
        vector<int> CardSets = writeCardSets();//セットしたカードIDをvectorで保持
        vector<Card> cards;//帰り値用, カードのリスト
        vector<string> splitString;//ファイル読み込み時の文字列を分割して入れる変数
        string line;//ファイル読み込み時の文字列をそのまま入れる変数
        Card nowCard;//代入用変数
        int i = 0, j = 0;//ループ処理用変数
        ifstream files("../data/CardData");//ファイル読み込み
        if(files.fail()){
            cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
        }
        getline(files, line);
        int cardNum = stoi(line);//カード数を代入
        while(i < CardSets.size()){
            if(CardSets.at(i) == j){
                getline(files, line);
                nowCard.putCardText(line);//テキストデータを代入
                getline(files, line);
                nowCard.putCardData(line);//数値データを代入
                cards.push_back(nowCard);//カードをリストに入れる
                i++;
            }else{
                getline(files, line);
                getline(files, line);
                j++;
            }
        }
        return cards;
    }

    vector<bool> writeHasCard(void){//カードを所持しているかのフラグのリストをvectorで返す関数
        vector<bool> output;//帰り値用, カードフラグのリスト
        vector<string> puts;//ファイル読み込み時の文字列を分割して入れる変数
        string line;//ファイル読み込み時の文字列をそのまま入れる変数
        ifstream files("../data/SaveData");//ファイル読み込み
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

    vector<int> writeCardSets(void){//セットカードのIDのリストをvectorで返す関数
        vector<int> output;//帰り値用, セットしたカードIDのリスト
        vector<string> puts;//ファイル読み込み時の文字列を分割して入れる変数
        string line;//ファイル読み込み時の文字列をそのまま入れる変数
        ifstream files("../data/SaveData");//ファイル読み込み
        if(files.fail()){
            cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
        }
        getline(files, line);
        getline(files, line);
        puts = split(line, ' ');//putsに分割後を入れる
        for(int i = 0; i < puts.size(); i++){//セットカードに対してリストを作成するループ処理
            output.push_back(stoi(puts.at(i)));
        }
        sort(output.begin(), output.end());//セットカードを昇順にソート
        return output;
    }

    vector<string> split(string str, char separator){//strをseparatorで分割する関数
        vector<string> output;//帰り値用, 分割後の文字列のリスト
        stringstream getString(str);//分割後の一時保存用の変数
        string x;//分割後の一時保存用の変数
        while(getline(getString, x, separator)) output.push_back(x);
        return output;
    }
};