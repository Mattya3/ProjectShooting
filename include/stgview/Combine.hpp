#include <bits/stdc++.h>
#include <internal/battle/Battle.hpp>

namespace stgview {
using std::pair;
using std::string;
using std::vector;

class Combine {

  public:
    explicit Combine() = default;

  private:
    int score;//現在のスコアを保管する
    /// ここで適当なinternalの変数を定義する
    // Battle bt; ChangeCardStructure ccs; など

  public:
    /// 実装は任せる
    inline int GetScoreToShowInResult() { return 500;/*採取的にはscoreを返すよう直したい*/ }
    inline int GetBestScore() {
      int best = battle.callBestScore();
      if(score > best) battle.writeBestScore();
    }

    /// @brief リザルト画面で見せるためのカードのファイル名と新規取得情報を取得
    /// @return ファイル名(=*.png)と新規取得かどうかを表すboolのvector
    inline vector<pair<string, bool>> GetCardsAcquiredToShowInResult() {
        return {{
                    "ansicard/card2.png",
                    true,
                },
                {
                    "ansicard/card2.png",
                    true,
                },
                {
                    "ansicard/card2.png",
                    false,
                },
                {
                    "ansicard/card2.png",
                    true,
                },
                {
                    "ansicard/card2.png",
                    false,
                }};
    }
};
extern Combine combine;
} // namespace stgview
