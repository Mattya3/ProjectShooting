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

  public:
    const int WindowWidth = 700, WindowHeight = 650;
    const int SX = 10, SY = 675; // 左上中心座標
    Location game_domain;
    void limit_my_fighter_loc(Location &loc) {
        double cx = loc.sx - loc.xlen / 2;
        double cy = loc.sy - loc.ylen / 2;
        if(cx < game_domain.sx) {
            loc.sx = game_domain.sx+loc.xlen/2;
        }
        if(cx > game_domain.sx + game_domain.xlen) {
            loc.sx = game_domain.sx + game_domain.xlen+loc.xlen/2;
        }
        if(cy < game_domain.sy) {
            loc.sy = game_domain.sy+loc.ylen/2;
        }
        if(cy > game_domain.sy + game_domain.ylen) {
            loc.sy = game_domain.sy + game_domain.ylen+loc.ylen/2;
        }
    }
    Game(/* args */);
    ~Game();
};

Game::Game(/* args */) {
    game_domain = Location(SX, SY, WindowWidth, WindowHeight);
}

Game::~Game() {}
