#include <GameEngine/Game.hpp>
#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/BattleScene.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/Title_Scene.hpp>

BattleScene::BattleScene(GLFWwindow *window1) {
    register_callback_resolver::init(*this, window1); // コールバック関数を登録
    bullet = make_unique<PngTexture>("battle/bulletMe.png",
                                     Location(-0.8, -0.8, 0.05, 0.05));

    btn_go_next_scene = make_unique<NextSceneButton>(
        Location(-0.6, -0.4, 1.2, 0.3), "test_img/go_title.png");
    bullet_enemy = make_unique<PngTexture>("battle/bulletEnemy.png",
                                           Location(-0.8, -0.8, 0.005, 0.005));
    auto x = make_unique<PngTexture>("battle/bulletMe.png",
                                     Location(-0.8, -0.8, 0.05, 0.05));
    enemies.emplace_back(make_unique<PngTexture>(
        "battle/bulletMe.png", Location(-0.8, -0.8, 0.05, 0.05)));
    Game game;
    Location g(10, 675, game.WindowWidth, game.WindowHeight);
    Button_anyTimes *game_space = new Button_anyTimes(g);
    game_space->set_color(0, 0, 1);

    while(!glfwWindowShouldClose(window1)) {
        glClear(GL_COLOR_BUFFER_BIT);
        show_component();
        btn_go_next_scene->button_view();
        bullet->view();
        game_space->button_filled_view();

        for(auto &&l : bullets_loc) {
            bullet->view_clone(l);
            l.sy += 0.0018;
        }
        for(auto &&e : bullets_loc_enemy) {
            bullet_enemy->view_clone(e);
            e.sy -= 0.002;
        }
        double vx, vy;
        vx = vy = 0;
        if(wp) {
            vy += velocity;
        }
        if(sp) {
            vy -= velocity;
        }
        if(ap) {
            vx -= velocity;
        }
        if(dp) {
            vx += velocity;
        }
        my_fighter.change_loc(vx, vy);
        game.limit_my_fighter_loc(my_fighter.get_loc());
        my_fighter.view();

        glfwSwapBuffers(window1);
        glfwPollEvents();
        if(btn_go_next_scene->next_scene) {
            break;
        }
    }
    if(btn_go_next_scene->next_scene) {
        Title_scene ts(window1);
    }
}

void BattleScene::key_callback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
    auto control_key_flag = [&](int key_id, bool &flag) {
        if(key == key_id) {
            if(action == GLFW_PRESS) {
                flag = true;
            } else if(action == GLFW_RELEASE) {
                flag = false;
            }
        }
    };
    control_key_flag(GLFW_KEY_W, wp);
    control_key_flag(GLFW_KEY_A, ap);
    control_key_flag(GLFW_KEY_S, sp);
    control_key_flag(GLFW_KEY_D, dp);

    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        bullets_loc.push_back(my_fighter.get_loc().clone());
    }
    if(key == GLFW_KEY_E && action == GLFW_PRESS) {
        auto tm = my_fighter.get_loc().clone();
        tm.sy += 0.7;
        tm.xlen = 0.1;
        tm.ylen = 0.1;
        bullets_loc_enemy.push_back(tm);
    }
    if(key == GLFW_KEY_R && action == GLFW_PRESS) {
        // my_fighter->rotate += 10;
        my_fighter.change_rotate();
    }
    if(key == GLFW_KEY_V && action == GLFW_PRESS) {
        velocity += 0.001;
    }
}
// void BattleScene::render(){}
BattleScene::~BattleScene() {}
