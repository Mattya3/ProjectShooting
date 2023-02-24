#include <stgview/Combine.hpp>
#include <stgview/ResultScene.hpp>
namespace stgview {
/// 最初から決まっているものはコンストラクタに書くことができる
ResultScene::ResultScene() {
    best_score_ypos = 0.4;
    score_ypos = 0.65;
    sbfw::ElemInfo score{{-0.4, score_ypos}, "DarkBlue/ResultString/SCORE.png"};
    sbfw::ElemInfo best{{-0.55, best_score_ypos + 0.003f},
                        "DarkBlue/ResultString/Best.png"};
    sbfw::ElemInfo bestscore{{-0.3, best_score_ypos},
                             "DarkBlue/ResultString/SCORE.png"};
    sbfw::ElemInfo result{{0, 0.9}, "DarkBlue/ResultString/RESULT.png", 1.3};
    sbfw::ElemInfo getcard{{-0.8, 0.2}, "DarkBlue/ResultString/GetCards.png"};
    this->AddImage(score);
    this->AddImage(best);
    this->AddImage(bestscore);
    this->AddImage(result);
    this->AddImage(getcard);
}
void ResultScene::layer_front() {
    /// scoreのアニメーション表示
    if(GetFrameCnt() < draw_score_animation_frame) {
        num_display.Draw(nowscore_fix, {0.3, score_ypos});
        nowscore_fix = int(1.0f * GetFrameCnt() * nowscore_dif);
    } else {
        num_display.Draw(nowscore, {0.3, score_ypos});
    }

    /// best scoreのアニメーション表示
    if(GetFrameCnt() < draw_score_animation_frame) {
        num_display.Draw("", {0.3, best_score_ypos});
    } else if(GetFrameCnt() < draw_score_animation_frame * 2) {
        num_display.Draw(bestscore_fix, {0.3, best_score_ypos});
        bestscore_fix =
            int(1.0f * (GetFrameCnt() - draw_score_animation_frame) *
                bestscore_dif);
    } else {
        num_display.Draw(bestscore, {0.3, best_score_ypos});
    }
}

/// @brief 画面遷移時の初期化
void ResultScene::InitAfterTransition() {
    nowscore = combine.GetScoreToShowInResult();
    bestscore = combine.GetBestScore();
    bestscore_fix = nowscore_fix = 0;
    bestscore_dif = float(bestscore) / float(draw_score_animation_frame);
    nowscore_dif = float(nowscore) / float(draw_score_animation_frame);

    auto cardfnames = combine.GetCardsAcquiredToShowInResult();
    DataOf2D draw_start_pos = {-0.65, 0.0f}, p = draw_start_pos;

    int cnt = 0;
    for(auto &&[fname, is_new] : cardfnames) {
        this->AddImage(fname, p, 0.8);
        p += {0.45, 0.0f};
        ++cnt;
        if(cnt >= 4) {
            p = draw_start_pos - DataOf2D(0.0f, 0.35f);
        }
    }
}
} // namespace stgview
