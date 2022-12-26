#include <component/Image.hpp>
#include <component/RemainingStatus.hpp>
#include <internal/battle/Battle.hpp>

#include <GameEngine/CenterLocation.hpp>
#include <bits/stdc++.h>
#include <scenes/Scene.hpp>
using namespace std;
class BattleScene : Scene {
    using Scene::Scene;

  private:
    // キーcallback用変数
    const int WindowWidth = 440, WindowHeight = 660;
    const int SX = 20, SY = 20; //  左上中心座標
    bool wp = false, ap = false, sp = false, dp = false, spacep = false;
    PngTexture heart = PngTexture("status/redheart.png");
    PngTexture gray_heart = PngTexture("status/heart.png");
    RemainingStatus life =
        RemainingStatus(DataOf2D(0.3, 0), heart, gray_heart, 5);
    vector<Location> bullets_loc_enemy; // 敵の弾の位置
    Location game_domain = Location(SX, SY, WindowWidth, WindowHeight);
    CenterLocation domain = CenterLocation(game_domain);

    // 画面上の要素
    // ポインタでないとオーバーライドができないのでスマートポインタで宣言
    vector<unique_ptr<PngTexture>> enemies; // 敵たち
    NextSceneButton *btn_go_next_scene;

  private:
    DataOf2D to_correctxy(pair<int, int> pii) {
        pii.first += 20;
        pii.second += 20;
        float x = float(pii.first);
        float y = float(pii.second);
        x /= Setting::WINDOW_width / 2;
        y /= Setting::WINDOW_height / 2;
        y = 1 - y;
        x = x - 1;
        return {x, y};
    }
    Location to_Location(GamePointMono gpm, int w, int h) {
        auto pp = to_correctxy(gpm.position);
        float ww = float(w) / Setting::WINDOW_width * 2;
        float hh = float(h) / Setting::WINDOW_height * 2;
        return Location(pp.x - ww / 2, pp.y - hh / 2, ww,hh);
    }

  public:
    Battle bt;

    PngTexture myfighter = PngTexture("battle/me.png");

    void operate_my_fighter(bool w, bool a, bool s, bool d) {
        bt.inputMoving(w, a, s, d);
    }
    void view_rotated_myfighter() {
        auto x = bt.viewer.callHero();
        float rotate = x.keyNum * 180 / M_PI;
        auto [px, py] = x.position;
        cout << px << "," << py << endl;
        auto l = to_Location(x, x.size, x.size);
        glPushMatrix();
        glTranslatef(l.sx + l.xlen / 2, l.sy + l.ylen / 2, 0);
        glRotatef(rotate, 0, 0, 1);
        glTranslatef(-l.sx - l.xlen / 2, -l.sy - l.ylen / 2, 0);
        myfighter.view_clone(l);
        glPopMatrix();
    }

  private:
  public:
    void key_callback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) override;

    BattleScene(GLFWwindow *window1);
    ~BattleScene();
};
