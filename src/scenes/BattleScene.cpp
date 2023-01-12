#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/BattleScene.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/Title_Scene.hpp>

#include <DataOf2D.hpp>

void filled_view(Location l, float r, float g, float b) {
    glBegin(GL_POLYGON);
    glColor3d(r, g, b);
    glVertex2d(l.sx, l.sy);
    glVertex2d(l.sx + l.xlen, l.sy);
    glVertex2d(l.sx + l.xlen, l.sy + l.ylen);
    glVertex2d(l.sx, l.sy + l.ylen);
    glEnd();
}

void show_point(double x, double y, char c) {
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
    // debug
    // PngTexture testboss("ic_launcher.png", Location(-0.3, 0.6, 0.2, 0.2));
    PngTexture testboss("ic_launcher.png", Location(-0.5, -0.5, 1.0, 1.0));

    // end debug

    double prev_time = glfwGetTime();
    double start_time = glfwGetTime();
    bt.start(0);
    bool go_Title_by_GameOver = false;

    while(!glfwWindowShouldClose(window1)) {
        glClear(GL_COLOR_BUFFER_BIT);
        filled_view(g, 0.2, 0.2, 0.2);
        show_component();
        bt.timer();

        now_time = glfwGetTime();
        double era = now_time - start_time;

        if(is_gameover) {
            if(now_time - game_end_time > 3) {
                go_Title_by_GameOver = true;
            }
            render_game_over();
            life.view(0);
            life2.view(0);
            testboss.view();
        } else {
            render_dynamic_view();
            life.view(bt.viewer.callHp());
            life2.view(bt.viewer.callHp());
            life3.view(bt.viewer.callHp());
        }

        glfwSwapBuffers(window1);
        glfwPollEvents();
        if(btn_go_next_scene->next_scene) {
            break;
        }
        if(go_Title_by_GameOver) {
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
    if(key == GLFW_KEY_J && action == GLFW_PRESS) {
        bt.inputLevelUp(0);
    }
    if(key == GLFW_KEY_K && action == GLFW_PRESS) {
        bt.inputLevelUp(1);
    }
    if(key == GLFW_KEY_L && action == GLFW_PRESS) {
        bt.inputLevelUp(2);
    }
}
// void BattleScene::render(){}
BattleScene::~BattleScene() {
    // delete btn_go_next_scene;
}
