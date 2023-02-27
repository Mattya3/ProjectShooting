#pragma once
#include <bits/stdc++.h>
#include <internal/BestScore.hpp>
#include <internal/battle/Battle.hpp>
#include <internal/card/CardHas.hpp>

namespace stgview {
using std::pair;
using std::string;
using std::vector;

class Combine {

  public:
    explicit Combine() = default;

  private:
    int score = 0; // 現在のスコアを保管する
    /// ここで適当なinternalの変数を定義する
    // Battle bt; ChangeCardStructure ccs; など

  public:
    inline void putScore(int now) { score = now; }
    /// 実装は任せる
    inline int GetScoreToShowInResult() { return score; }

    inline int GetBestScore() {
        int best = callBestScore();
        if(score > best) writeBestScore(score);
        return best;
    }

    /// @brief リザルト画面で見せるためのカードのファイル名と新規取得情報を取得
    /// @return ファイル名(=*.png)と新規取得かどうかを表すboolのvector
    inline vector<pair<string, bool>> GetCardsAcquiredToShowInResult() {
        CardHas newCard;
        vector<pair<string, bool>> output = newCard.getNewCard(score);
        return output;
    }
};
extern Combine combine;
} // namespace stgview
