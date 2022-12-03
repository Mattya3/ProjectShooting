#include <bits/stdc++.h>
#include "../include/StructureData.hpp"
using namespace std;

class StructureData{
public:
    vector<Card> callCardSets(void){//セットカードのリストをvectorで返す関数
        vector<int> CardSets = readCardSets();//セットしたカードIDをvectorで保持
        vector<Card> cards;//帰り値用, カードのリスト
        string text, data;//ファイル読み込み時の文字列をそのまま入れる変数
        Card nowCard;//代入用変数
        int i = 0, j = 0;//ループ処理用変数
        ifstream files("../data/CardData");//ファイル読み込み
        if(files.fail()){
            cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
        }
        getline(files, text);//一行目のカード数を記入
        getline(files, text);//No.0のテキストの記入
        getline(files, data);//No.0のデータの記入
        while(i < CardSets.size()){//セットカードリストを作成するループ処理
            if(CardSets.at(i) == j){//セットカードリストに存在する
                nowCard.putCardText(text);//テキストデータを代入
                nowCard.putCardData(i, data);//数値データを代入
                cards.push_back(nowCard);//カードをリストに入れる
                i++;
            }else{//セットカードリストに存在しない
                getline(files, text);//各No.のテキストの記入
                getline(files, data);//各No.のデータの記入
                j++;
            }
        }
        return cards;
    }

    vector<int> readCardSets(void){//セットカードのIDのリストをvectorで返す関数
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

    void writeCardSets(vector<int> list){//新たなセットカードをファイルに書き込む関数
        string line1;//変更しない所持カードリストの保持用
        string line2 = to_string(list.at(0)) + " " + to_string(list.at(1)) + " " + to_string(list.at(2));//変更後のセットカードリスト
        ifstream file1("../data/SaveData");//ファイル読み込み
        if(file1.fail()){
            cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
        }
        getline(file1, line1);
        ofstream file2("../data/SaveData", ios::out);//ファイル読み込み
        if(file2.fail()){
            cerr << "Error: not open file" << endl;//ファイル読み込みエラー発生時の処理
        }
        file2 << line1 << endl;
        file2 << line2 << endl;
        file2.close();
    }
};