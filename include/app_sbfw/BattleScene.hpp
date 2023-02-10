#pragma once
#include <sbfw.hpp>

#include <Image.hpp>
#include <RemainingStatus.hpp>

#include <internal/battle/Battle.hpp>
#include <internal/battle/GamePointMono.hpp>
#include <internal/battle/GamePointView.hpp>

#include <bits/stdc++.h>

using namespace std;
class BattleScene : public sbfw::scene::SimpleScene {
  public:
    RemainingStatus life{
        5, {0.2, -0.2}, img_manager.ProvideImage("status/redheart.png")};
    shared_ptr<sbfw::scene::SimpleScene> result_scene = nullptr;

    PngTexture testboss{"ic_launcher.png", Location(-0.5, -0.5, 1.0, 1.0)};
    double prev_time;
    double start_time;
    bool go_Title_by_GameOver = false;
    int WINDOW_width = 800, WINDOW_height = 700;
    inline void to_canonical_xy(float &x, float &y) {
        x /= WINDOW_width / 2;
        y /= WINDOW_height / 2;
        y = 1 - y;
        x = x - 1;
    }
    inline void to_canonical_xy(double &x, double &y) {
        x /= WINDOW_width / 2;
        y /= WINDOW_height / 2;
        y = 1 - y;
        x = x - 1;
    }

  protected:
    void layer_front() {
        bt.timer();

        now_time = glfwGetTime();
        double era = now_time - start_time;

        if(is_gameover) {
            if(now_time - game_end_time > 2) {
                go_Title_by_GameOver = true;
                GoNextScene(result_scene);
            }
            render_game_over();
            testboss.view();
        } else {
            render_dynamic_view();
            // life.view(bt.viewer.callHp());
            life.Draw(bt.viewer.callHp());
        }
    }
    void layer_back() override { filled_view___(g, 0.2, 0.2, 0.2); }

    void InitAfterTransition() override {
        prev_time = glfwGetTime();
        start_time = glfwGetTime();
        bt.start(0);
        go_Title_by_GameOver = false;
        is_gameover = false;
    }

  private:
    // キーcallback用変数
    const int WindowWidth = 444, WindowHeight = 660;
    const int SX = 18, SY = 20; //  左上中心座標
    Location g = Location(SX, SY, WindowWidth, WindowHeight);

    // GameOver時少し表示する用のbuffer
    GamePointMono buf_hero;
    vector<GamePointMono> buf_hero_bullet, buf_enemy, buf_enemy_bullet;

    double game_end_time;
    double now_time;
    bool is_gameover = false;
    bool wp = false, ap = false, sp = false, dp = false, spacep = false;
    PngTexture heart = PngTexture("status/redheart.png");
    PngTexture gray_heart = PngTexture("status/heart.png");
    PngTexture ene_bullet =
        PngTexture("battle/bulletEnemy.png", Location(-0.8, -0.8, 0.05, 0.05));
    PngTexture enemy_tex = PngTexture("battle/enemy.png");

    PngTexture mybullet = PngTexture("battle/bulletMe.png");

    vector<Location> bullets_loc_enemy; // 敵の弾の位置
    Location game_domain = Location(SX, SY, WindowWidth, WindowHeight);

  private:
    DataOf2D to_correctxy(pair<int, int> pii) {
        pii.first += 20;
        pii.second += 20;
        float x = float(pii.first);
        float y = float(pii.second);
        x /= WINDOW_width / 2;
        y /= WINDOW_height / 2;
        y = 1 - y;
        x = x - 1;
        return {x, y};
    }
    Location to_Location(GamePointMono gpm, int w, int h) {
        auto pp = to_correctxy(gpm.position);
        float ww = float(w) / WINDOW_width * 2;
        float hh = float(h) / WINDOW_height * 2;
        return Location(pp.x - ww / 2, pp.y - hh / 2, ww, hh);
    }
    Location to_Location(GamePointMono gpm) {
        auto pp = to_correctxy(gpm.position);
        int w = gpm.size;
        int h = gpm.size;
        float ww = float(w) / WINDOW_width * 2;
        float hh = float(h) / WINDOW_height * 2;
        return Location(pp.x - ww / 2, pp.y - hh / 2, ww, hh);
    }
    void render_dynamic_view();
    void render_game_over();
    void render_static_view();

  public:
    Battle bt;

    PngTexture myfighter = PngTexture("battle/me.png");

    void operate_my_fighter(bool w, bool a, bool s, bool d) {
        bt.inputMoving(w, a, s, d);
    }
    void view_rotated_myfighter(GamePointMono x) {
        float rotate = x.keyNum * 180 / M_PI;
        auto l = to_Location(x);
        glPushMatrix();
        glTranslatef(l.sx + l.xlen / 2, l.sy + l.ylen / 2, 0);
        glRotatef(rotate, 0, 0, 1);
        glTranslatef(-l.sx - l.xlen / 2, -l.sy - l.ylen / 2, 0);
        myfighter.view_clone(l);
        glPopMatrix();
    }

  protected:
    void key_callback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) override;
};
