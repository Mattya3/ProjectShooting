#include <GameEngine/Game.hpp>
Game::Game(/* args */) {
    game_domain = Location(SX, SY, WindowWidth, WindowHeight);
    domain = CenterLocation(game_domain);
    auto [cx, cy] = domain.get_cxy();
    auto [lx, ly] = domain.get_len();
    up_b = ly + cy;
    down_b = ly - cy;
    right_b = lx + cx;
    left_b = lx - cx;
}

Game::~Game() {}
