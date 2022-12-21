#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/BattleScene.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/Title_Scene.hpp>

#include <DataOf2D.hpp>
#include <internal/battle/GamePointMono.hpp>
#include <internal/battle/GamePointView.hpp>

void filled_view(Location l, float r, float g, float b) {
    glBegin(GL_POLYGON);
    glColor3d(r, g, b);
    glVertex2d(l.sx, l.sy);
    glVertex2d(l.sx + l.xlen, l.sy);
    glVertex2d(l.sx + l.xlen, l.sy + l.ylen);
    glVertex2d(l.sx, l.sy + l.ylen);
    glEnd();
}

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
    cout << "here ok " << endl;
    enemies.emplace_back(make_unique<PngTexture>(
        "battle/bulletMe.png", Location(-0.8, -0.8, 0.05, 0.05)));
    PngTexture ene("battle/bulletEnemy.png", Location(-0.8, -0.8, 0.05, 0.05));
    PngTexture mybullet("battle/bulletMe.png");
    Location g(game.SX, game.SY, game.WindowWidth, game.WindowHeight);
    Button_anyTimes *game_space = new Button_anyTimes(g);
    game_space->set_color(0, 0, 1);
    Button_anyTimes *red = new Button_anyTimes(g);
    red->set_color(1, 0, 0);
    Button_anyTimes *black = new Button_anyTimes(g);
    black->set_color(0.1, 0.1, 0.1);
    int cnt_of_attacked = 0;
    PngTexture testboss("ic_launcher.png", Location(-0.3, 0.6, 0.2, 0.2));
    PngTexture sample("ic_launcher.png");
    PngTexture me("battle/me.png");

    double prev_time = glfwGetTime();
    double start_time = glfwGetTime();
    game.bt.start(0);
    float ratio = 0.5;
    while(!glfwWindowShouldClose(window1)) {
        glClear(GL_COLOR_BUFFER_BIT);
        game.rotate_my_fighter();
        filled_view(g, 0.2, 0.2, 0.2);
        show_component();
        // btn_go_next_scene->button_view();
        game.bt.timer();

        double now_time = glfwGetTime();
        double era = now_time - start_time;
        sample.view_clone(Location(0, 0, 50, 50));
 



        game.bt.viewer.callEnemy();
        auto d = game.bt.viewer.callHeroBullet();
        for(auto &&i : d) {
            mybullet.view_clone(to_Location(i, 32, 32));
        }

        auto en = game.bt.viewer.callEnemy();
        for(auto &&i : en) {
            sample.view_clone(to_Location(i, 32, 32));
        }

        auto ebs = game.bt.viewer.callEnemyBullet();
        for(auto &&i : ebs) {
            ene.view_clone(to_Location(i, 16, 16));
        }

        game.operate_my_fighter(wp, ap, sp, dp);
        game.view();

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
    control_key_flag(GLFW_KEY_SPACE, spacep);
    game.bt.inputShooting(spacep);

    if(key == GLFW_KEY_R && action == GLFW_PRESS) {
        game.rotate_my_fighter();
    }
    if(key == GLFW_KEY_V && action == GLFW_PRESS) {}
}
// void BattleScene::render(){}
BattleScene::~BattleScene() {
    // delete btn_go_next_scene;
}
