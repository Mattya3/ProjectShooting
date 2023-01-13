#include <internal/card/StructureData.hpp>

vector<Card> StructureData::callCardSets(void){//セットカードのリストをvectorで返す関数
    vector<short> CardSets = readCardSets();//セットしたカードIDをvectorで保持
    vector<Card> cards(3);//帰り値用, カードのリスト
    vector<bool> flag(3, false);
    string text, data;//ファイル読み込み時の文字列をそのまま入れる変数
    Card nowCard;//代入用変数
    short i = 0, j = 0;//ループ処理用変数
    ifstream files((current_path() / filesystem::path("data/CardData")).c_str());//ファイル読み込み
    if(files.fail()){
        cerr << "Error: not open CardData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(files, text);
    getline(files, text);
    getline(files, data);
    while(!(flag.at(0) && flag.at(1) && flag.at(2))){//全てのセットカードの反映が終了するまで
        for(int i = 0; i < CardSets.size(); i++){//所持カード全ての探索
            if(CardSets.at(i) == j){//セットカードリストに存在する
                nowCard.putCardText(text);
                nowCard.putCardData(j, data);
                cards.at(i) = nowCard;
                flag.at(i) = true;
            }
        }
        getline(files, text);
        getline(files, data);
        j++;
    }
    return cards;
}

vector<short> StructureData::readCardSets(void){//セットカードのIDのリストをvectorで返す関数
    vector<short> output;//帰り値用, セットしたカードIDのリスト
    vector<string> puts;//ファイル読み込み時の文字列を分割して入れる変数
    string line;//ファイル読み込み時の文字列をそのまま入れる変数
    ifstream files((current_path() / filesystem::path("data/SaveData")).c_str());//ファイル読み込み
    if(files.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(files, line);
    getline(files, line);
    puts = split(line, ' ');
    for(int i = 0; i < puts.size(); i++) output.push_back(stoi(puts.at(i))); //セットカードのidのリストの作成
    return output;
}

void StructureData::writeCardSets(vector<short> list){//新たなセットカードをファイルに書き込む関数
    string line1;//変更しない所持カードリストの保持用
    string line2 = to_string(list.at(0)) + " " + to_string(list.at(1)) + " " + to_string(list.at(2));//変更後のセットカードリスト
    ifstream file1((current_path() / filesystem::path("data/SaveData")).c_str());//ファイル読み込み
    if(file1.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(file1, line1);
    ofstream file2((current_path() / filesystem::path("data/SaveData")).c_str(), ios::out);//ファイル読み込み
    if(file2.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    file2 << line1 << endl;
    file2 << line2 << endl;
    file2.close();
}