#include <DataOf2D.hpp>

#include <SBFW/extension/NumberDisplay.hpp>
#include <SBFW/unit.hpp>

#include <GLFW/glfw3.h>

#include "Location.hpp"
#include "PngTexture.hpp"
#include "RemainingStatus.hpp"

#include <internal/battle/Battle.hpp>
#include <internal/battle/GamePointMono.hpp>
#include <internal/battle/GamePointView.hpp>
#include <internal/card/ChangeStructure.hpp>

namespace sbfw {
extern int window_height, window_width;
} // namespace sbfw

class GameScene : public sbfw::scene::SimpleScene {
  private:
    using Pdu = sbfw::texture::PartialDynamicUnit;

  public:
    GameScene() = default;

  private:
    /// @brief 毎回の描画ループで呼び出される関数
    /// @details
    /// これをオーバーライドしておけば、親クラス側でGLFWの設定を行い描画される
    /// なので適当なクラスのDrawメソッドをここで呼べばよい
    void layer_front() override;

    /// @brief このシーンに遷移した時に初期化する
    /// これが呼ばれるタイミングはシーン遷移時に毎回であって、コンストラクタのような変数定義時に一回だけとは違う
    void InitAfterTransition() override;

    /// @brief キーボード入力を受け付ける関数
    void key_callback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) override;

    /// @brief 結合作業
    void CombineInternalBattle();
    void DrawRotatedMyfighter(GamePointMono x);

  public:
    /// @brief
    /// ゲームオーバ時の遷移先画面を指定する(ボタン遷移(=DefTransition())ではない場合は個別に対応する)
    std::shared_ptr<sbfw::scene::SimpleScene> result_scene = nullptr;

  private:
    Battle bt;
    bool wp = false, ap = false, sp = false, dp = false, spacep = false;
    bool is_gameover = false;
    const DataOf2D leftup = ToRegularXYpos(20, 20);
    const DataOf2D rightdown = ToRegularXYpos(460, 680);
    const float gamefield_left = leftup.x, gamefield_right = rightdown.x;
    const float gamefield_up = leftup.y, gamefield_down = rightdown.y;
    const int WindowWidth = 444, WindowHeight = 660;
    const int SX = 18, SY = 20; //  左上中心座標
    Location g = Location(SX, SY, WindowWidth, WindowHeight);

    sbfw::ext::NumberDisplay number_display;
    RemainingStatus life_point{
        5, {0.3, 0.8}, sbfw::img_manager.ProvideImage("status/redheart.png")};
    PngTexture heart = PngTexture("status/redheart.png");
    PngTexture gray_heart = PngTexture("status/heart.png");
    PngTexture ene_bullet =
        PngTexture("battle/bulletEnemy.png", Location(-0.8, -0.8, 0.05, 0.05));
    PngTexture enemy_tex = PngTexture("battle/enemy.png");
    PngTexture myfighter = PngTexture("battle/me.png");
    PngTexture mybullet = PngTexture("battle/bulletMe.png");

    struct ImageDefinitions {

        std::tuple<int, DataOf2D, int, int> atlas =
            sbfw::img_manager.ProvideImageGetWH("atlasv2.png");

      public:
        Pdu yellow_ball{0, 0, 32, 32, atlas};
        Pdu blue_ball{0, 32, 32, 32, atlas};
        Pdu green_ball{32, 32, 32, 32, atlas};
        Pdu red_ball{32, 0, 32, 32, atlas};

        Pdu my_fighter{64, 0, 64, 64, atlas};
        Pdu cat{0, 64, 64, 64, atlas};
        Pdu droid{64, 64, 64, 64, atlas};

        Pdu red_heart{128, 0, 32, 32, atlas};
        Pdu gray_heart{128, 32, 32, 32, atlas};
        Pdu red_star{128, 64, 32, 32, atlas};
        Pdu gray_star{128, 96, 32, 32, atlas};

    } gview{};
    inline DataOf2D ToRegularXYpos(unsigned x, unsigned y) {
        float tx = x, ty = y;
        tx /= sbfw::window_width / 2;
        ty /= sbfw::window_height / 2;
        ty = 1 - ty;
        tx = tx - 1;
        return {tx, ty};
    }

  public:
    inline void to_canonical_xy(float &x, float &y) {
        x /= sbfw::window_width / 2;
        y /= sbfw::window_height / 2;
        y = 1 - y;
        x = x - 1;
    }
    inline void to_canonical_xy(double &x, double &y) {
        x /= sbfw::window_width / 2;
        y /= sbfw::window_height / 2;
        y = 1 - y;
        x = x - 1;
    }
    Location to_Location(GamePointMono gpm, int w, int h) {
        auto pp = to_correctxy(gpm.position);
        float ww = float(w) / sbfw::window_width * 2;
        float hh = float(h) / sbfw::window_height * 2;
        return Location(pp.x - ww / 2, pp.y - hh / 2, ww, hh);
    }
    Location to_Location(GamePointMono gpm) {
        auto pp = to_correctxy(gpm.position);
        int w = gpm.size;
        int h = gpm.size;
        float ww = float(w) / sbfw::window_width * 2;
        float hh = float(h) / sbfw::window_height * 2;
        return Location(pp.x - ww / 2, pp.y - hh / 2, ww, hh);
    }
    DataOf2D to_correctxy(pair<int, int> pii) {
        pii.first += 20;
        pii.second += 20;
        float x = float(pii.first);
        float y = float(pii.second);
        x /= sbfw::window_width / 2;
        y /= sbfw::window_height / 2;
        y = 1 - y;
        x = x - 1;
        return {x, y};
    }
};
