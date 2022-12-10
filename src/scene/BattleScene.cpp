#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/BattleScene.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/Title_Scene.hpp>

BattleScene::BattleScene(GLFWwindow *window1) {
    register_callback_resolver::init(*this, window1);
    // PngTexture me("battle/me.png", Location(-0.8, -0.8, 0.4, 0.4));
    my_fighter = make_unique<PngTexture>("battle/me.png",
                                         Location(-0.8, -0.8, 0.2, 0.2));
    bullet = make_unique<PngTexture>("battle/bulletMe.png",
                                     Location(-0.8, -0.8, 0.1, 0.1));
    PngTexture go_select_card("test_img/go_title.png",
                              Location(-0.6, -0.4, 1.2, 0.3));

    NextSceneButton *b = new NextSceneButton(-0.6, -0.4, 1.2, 0.3);
    Button_anyTimes *transBtn = new Button_anyTimes(0.3, 0.3, 0.5, 0.5);
    b->set_color(0.5, 0.1, 0.8);
    this->add_button(b);
    transBtn->set_color(0.1, 0.8, 0.2);
    this->add_button(transBtn);
    int dir = 1;

    while(!glfwWindowShouldClose(window1)) {
        glClear(GL_COLOR_BUFFER_BIT);
        show_component();
        go_select_card.view();
        bullet->view();
        my_fighter->view();
        glfwSwapBuffers(window1);
        glfwPollEvents();
        if(b->next_scene) {
            break;
        }
    }
    if(b->next_scene) {
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
    if(wp) {
        my_fighter->loc.sy += velocity;
    }
    if(sp) {
        my_fighter->loc.sy -= velocity;
    }
    if(ap) {
        my_fighter->loc.sx -= velocity;
    }
    if(dp) {
        my_fighter->loc.sx += velocity;
    }
    if(key==GLFW_KEY_SPACE && action==GLFW_PRESS){
        bullet->loc.sx+=0.1;
        bullet->loc.sy+=0.1;
    }

    
}
BattleScene::~BattleScene() {}
