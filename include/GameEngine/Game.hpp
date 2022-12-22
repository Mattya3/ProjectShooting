#include "Event.hpp"
#include <GameEngine/subGameObject/GroupGameObject.hpp>
#include <GameEngine/subGameObject/MyFighter.hpp>
#include <component/Location.hpp>
#include <internal/battle/Battle.hpp>
#include <setting.hpp>

/**
 * @brief
 * ゲームはウィンドウの左側で行われる
 * ゲーム内座標とOpenGL座標系の対応など
 */
class Game {
  private:
    int time;
    Location game_domain;
    CenterLocation domain;
    double right_b, up_b, left_b, down_b;

  public:
    GroupGameObject bullets;
    Battle bt;

    PngTexture myfighter = PngTexture("battle/me.png");
    const int WindowWidth = 440, WindowHeight = 660;
    const int SX = 20, SY = 20; //  左上中心座標
    void operate_my_fighter(bool w, bool a, bool s, bool d) {
        bt.inputMoving(w, a, s, d);
        // limit_my_fighter_loc();
    }
    void view_rotated_myfighter() {
        float rotate = bt.viewer.callHero().keyNum * 180 / M_PI;
        auto x = bt.viewer.callHero();
        auto l = to_Location(x, x.size, x.size);
        glPushMatrix();
        glTranslatef(l.sx + l.xlen / 2, l.sy + l.ylen / 2, 0);
        glRotatef(rotate, 0, 0, 1);
        glTranslatef(-l.sx - l.xlen / 2, -l.sy - l.ylen / 2, 0);
        myfighter.view_clone(l);
        glPopMatrix();
    }
    Game(/* args */);
    ~Game();
};
