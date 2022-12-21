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

    MyFighter my_fighter = MyFighter("battle/me.png"); // 自機
    const int WindowWidth = 440, WindowHeight = 660;
    const int SX = 20, SY = 20; //  左上中心座標
    void operate_my_fighter(bool w, bool a, bool s, bool d) {
        bt.inputMoving(w, a, s, d);
        // limit_my_fighter_loc();
    }
    void rotate_my_fighter() {
        // my_fighter.change_rotate();
        my_fighter.rotate=bt.viewer.callHero().keyNum*180/M_PI;
        // my_fighter.get_pos().dump();
    }
    void view() {
        auto x =bt.viewer.callHero();
        my_fighter.view(to_Location(x, 32, 32));
    }
    Game(/* args */);
    ~Game();
};
