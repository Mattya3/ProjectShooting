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
    // map<double, vector<Event>> event_list;

  public:
    GroupGameObject bullets;
    Battle bt;

    MyFighter my_fighter = MyFighter("battle/me.png"); // 自機
    const int WindowWidth = 440, WindowHeight = 660;
    const int SX = 20, SY = 20; //  左上中心座標
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
            // my_fighter.accelerate(0, +1);
            bt.inputMoving(true);
            bt.inputAngle(M_PI / 2);
        } else {
            bt.inputMoving(false);
        }
        if(s) {
            // my_fighter.accelerate(0, -1);
            bt.inputMoving(true);
            bt.inputAngle(-M_PI / 2);
        } else {
            bt.inputMoving(false);
        }
        if(a) {
            // my_fighter.accelerate(-1, 0);
            bt.inputMoving(true);
            bt.inputAngle(M_PI);
        } else {
            bt.inputMoving(false);
        }
        if(d) {
            // my_fighter.accelerate(1, 0);
            bt.inputMoving(true);
            bt.inputAngle(0);
        } else {
            bt.inputMoving(false);
        }
        limit_my_fighter_loc();
    }
    void rotate_my_fighter() {
        my_fighter.change_rotate();
        my_fighter.get_pos().dump();
    }
    void view() {
        auto x = bt.viewer.callHero();
        my_fighter.get_pos().dump();
        my_fighter.set_pos(DataOf2D(x.position.first, x.position.second, 1.0));
        my_fighter.get_pos().dump();
        my_fighter.view();
    }
    Game(/* args */);
    ~Game();
};
