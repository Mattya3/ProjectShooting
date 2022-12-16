#include <GameEngine/subGameObject/GroupGameObject.hpp>
#include <GameEngine/subGameObject/MyFighter.hpp>
#include <component/Location.hpp>
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
    MyFighter my_fighter = MyFighter("battle/me.png"); // 自機
    const int WindowWidth = 440, WindowHeight = 660;
    const int SX = 20, SY = 20; // wwsssss 左上中心座標

    void reflect() { bullets.reflect(domain); }
    void limit_my_fighter_loc() {
        auto fixed_domain =
            CenterLocation(domain.get_cxy(),
                           domain.get_len() - my_fighter.get_pos().get_len());
        auto &&p = my_fighter.pos.c;
        p.x = min(p.x, fixed_domain.right());
        p.y = min(p.y, fixed_domain.up());
        p.x = max(p.x, fixed_domain.left());
        p.y = max(p.y, fixed_domain.down());
    }
    void operate_my_fighter(bool w, bool a, bool s, bool d) {
        if(w) {
            my_fighter.accelerate(0, +1);
        }
        if(s) {
            my_fighter.accelerate(0, -1);
        }
        if(a) {
            my_fighter.accelerate(-1, 0);
        }
        if(d) {
            my_fighter.accelerate(1, 0);
        }
        limit_my_fighter_loc();
    }
    void rotate_my_fighter() {
        my_fighter.change_rotate();
        my_fighter.get_pos().dump();
    }
    void view() { my_fighter.view(); }
    Game(/* args */);
    ~Game();
};
