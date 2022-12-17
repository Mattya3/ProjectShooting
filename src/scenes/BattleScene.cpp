#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/BattleScene.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/Title_Scene.hpp>

#include <internal/battle/GamePointMono.hpp>
#include <internal/battle/GamePointView.hpp>
void show_sphere(double x, double y, char c) {
    glBegin(GL_POLYGON);
    if(c == 'R') {
        glColor3d(1.0, 0.0, 0.0);
    } else if(c == 'G') {
        glColor3d(0.0, 1.0, 0.0);
    } else if(c == 'B') {
        glColor3d(0.0, 0.0, 1.0);
    }

    glVertex2d(x, y);
    glVertex2d(x + 0.01, y);
    glVertex2d(x + 0.01, y + 0.01);
    glVertex2d(x, y + 0.01);
    glEnd();
}
BattleScene::BattleScene(GLFWwindow *window1) {
    register_callback_resolver::init(*this, window1); // コールバック関数を登録
    btn_go_next_scene = new NextSceneButton(Location(-0.6, -0.4, 1.2, 0.3),
                                            "test_img/go_title.png");

    enemies.emplace_back(make_unique<PngTexture>(
        "battle/bulletMe.png", Location(-0.8, -0.8, 0.05, 0.05)));
    PngTexture ene("battle/bulletEnemy.png", Location(-0.8, -0.8, 0.05, 0.05));
    Location g(game.SX, game.SY, game.WindowWidth, game.WindowHeight);
    Button_anyTimes *game_space = new Button_anyTimes(g);
    game_space->set_color(0, 0, 1);
    Button_anyTimes *red = new Button_anyTimes(g);
    red->set_color(1, 0, 0);
    Button_anyTimes *black = new Button_anyTimes(g);
    black->set_color(0.1, 0.1, 0.1);
    int cnt_of_attacked = 0;
    PngTexture testboss("ic_launcher.png", Location(-0.3, 0.6, 0.2, 0.2));

    double prev_time = glfwGetTime();
    double start_time = glfwGetTime();
    GamePointView gpv;
    bt.start(0);
    while(!glfwWindowShouldClose(window1)) {
        glClear(GL_COLOR_BUFFER_BIT);
        show_component();
        btn_go_next_scene->button_view();
        bt.timer();

        double now_time = glfwGetTime();
        double era = now_time - start_time;
        if(5 <= era && era <= 8) {
            if(floor(era) == 5) {
                red->button_filled_view();
            } else if(floor(era) == 6) {
                black->button_filled_view();
            } else if(floor(era) == 7) {
                red->button_filled_view();
            } else if(floor(era) == 8) {
                black->button_filled_view();
            }
        } else {
            game_space->button_filled_view();
        }
        if(era >= 8.1) {
            testboss.view();
        }

        auto myFi = gpv.callHero();
        game.my_fighter.set_pos(
            DataOf2D(myFi.position.first, myFi.position.second));
        game.bullets.view();

        auto d = gpv.callHeroBullet();
        cout << "heroBullet size " << d.size() << endl;
        for(auto &&i : d) {
            ene.view_clone(Location(double(i.position.first),
                                    double(i.position.second), 0.05, 0.05));
        }

        // game.operate_my_fighter(wp, ap, sp, dp);
        game.view();

        game.reflect();
        game.bullets.proceed();
        game.limit_my_fighter_loc();

        glfwSwapBuffers(window1);
        glfwPollEvents();
        if(btn_go_next_scene->next_scene) {
            break;
        }
    }
    if(btn_go_next_scene->next_scene) {
        delete btn_go_next_scene;
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
        // game.bullets.push(game.my_fighter.get_pos().get_cxy());
        bt.inputShooting(true);
    }
    if(key == GLFW_KEY_E && action == GLFW_PRESS) {
        // auto tm = my_fighter.get_loc().clone();
        // tm.sy += 0.7;
        // tm.xlen = 0.1;
        // tm.ylen = 0.1;
        // bullets_loc_enemy.push_back(tm);
    }
    if(key == GLFW_KEY_R && action == GLFW_PRESS) {
        game.rotate_my_fighter();
    }
    if(key == GLFW_KEY_V && action == GLFW_PRESS) {}
}
// void BattleScene::render(){}
BattleScene::~BattleScene() {
    // delete btn_go_next_scene;
}
