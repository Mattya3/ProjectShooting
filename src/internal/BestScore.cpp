#include <internal/BestScore.hpp>

short callBestScore(){
    string line;
    ifstream file1((current_path() / filesystem::path("data/SaveData")).c_str());//ファイル読み込み
    if(file1.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(file1, line);
    getline(file1, line);
    getline(file1, line);
    return stoi(line);
}

void writeBestScore(short score){
    string line1;//変更しない所持カードリストの保持用
    string line2;
    ifstream file1((current_path() / filesystem::path("data/SaveData")).c_str());//ファイル読み込み
    if(file1.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    getline(file1, line1);
    getline(file1, line2);
    ofstream file2((current_path() / filesystem::path("data/SaveData")).c_str(), ios::out);//ファイル読み込み
    if(file2.fail()){
        cerr << "Error: not open SaveData" << endl;//ファイル読み込みエラー発生時の処理
    }
    file2 << line1 << endl;
    file2 << line2 << endl;
    file2 << score << endl;
    file2.close();
}