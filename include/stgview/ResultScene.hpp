#include <extension/NumberDisplay.hpp>
#include <sbfw.hpp>

#include <bits/stdc++.h>
namespace stgview {

class ResultScene : public sbfw::scene::SimpleScene {
  public:
    ResultScene();

  private:
    /// @brief 描画用関数
    void layer_front() override;

    /// @brief 画面遷移時の初期化
    void InitAfterTransition() override;

  private:
    sbfw::ext::NumberDisplay num_display;
    float best_score_ypos, score_ypos;

    /// @brief スコアを増やしながら表示するアニメーション用変数
    int bestscore, nowscore;
    int bestscore_fix, nowscore_fix;
    float bestscore_dif, nowscore_dif;
    const int draw_score_animation_frame = 120;
};
} // namespace stgview
