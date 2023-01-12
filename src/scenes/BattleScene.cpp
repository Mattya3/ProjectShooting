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

    Location g(SX, SY, WindowWidth, WindowHeight);
    PngTexture testboss("ic_launcher.png", Location(-0.3, 0.6, 0.2, 0.2));
    PngTexture sample("battle/enemy.png");
    GamePointMono gpmtest;
    gpmtest.position = {40, 40};
    gpmtest.size = 32;

    double prev_time = glfwGetTime();
    double start_time = glfwGetTime();
    bt.start(0);
    bool go_Title_by_GameOver=false;
    while(!glfwWindowShouldClose(window1)) {
        glClear(GL_COLOR_BUFFER_BIT);
        filled_view(g, 0.2, 0.2, 0.2);
        show_component();
        // btn_go_next_scene->button_view();
        bt.timer();

        double now_time = glfwGetTime();
        double era = now_time - start_time;

        life.view(bt.viewer.callHp());
        life2.view(bt.viewer.callHp());
        life3.view(bt.viewer.callHp());

        auto x = bt.viewer.callHero();
        view_rotated_myfighter(x);
        // testboss.view_clone(to_Location(x));
        // sample.view_clone(to_Location(x));

        bt.viewer.callEnemy();
        auto d = bt.viewer.callHeroBullet();
        for(auto &&i : d) {
            mybullet.view_clone(to_Location(i, i.size, i.size));
        }

        auto en = bt.viewer.callEnemy();
        for(auto &&i : en) {
            sample.view_clone(to_Location(i, i.size, i.size));
        }

        auto ebs = bt.viewer.callEnemyBullet();
        for(auto &&i : ebs) {
            ene.view_clone(to_Location(i, i.size, i.size));
        }

        operate_my_fighter(wp, ap, sp, dp);

        glfwSwapBuffers(window1);
        glfwPollEvents();
        if(btn_go_next_scene->next_scene) {
            break;
        }
        if(bt.viewer.callHp() < 0) {
            cout << "GameOver" << endl;
            go_Title_by_GameOver=true;
            break;
        }
    }
    if(btn_go_next_scene->next_scene || go_Title_by_GameOver) {
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
    bt.inputShooting(spacep);

    if(key == GLFW_KEY_R && action == GLFW_PRESS) {
        // rotate_my_fighter();
        life.decrement_stock();
    }
    if(key == GLFW_KEY_V && action == GLFW_PRESS) {}
}
// void BattleScene::render(){}
BattleScene::~BattleScene() {
    // delete btn_go_next_scene;
}
