#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/BattleScene.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/Title_Scene.hpp>

BattleScene::BattleScene(GLFWwindow *window1) {
    register_callback_resolver::init(*this, window1);

    my_fighter = make_unique<PngTexture>("battle/me.png",
                                         Location(-0.8, -0.8, 0.2, 0.2));
    bullet = make_unique<PngTexture>("battle/bulletMe.png",
                                     Location(-0.8, -0.8, 0.05, 0.05));

    NextSceneButton *go_next = new NextSceneButton(Location(-0.6, -0.4, 1.2, 0.3), "test_img/go_title.png");
    this->add_button(go_next);
    while(!glfwWindowShouldClose(window1)) {
        glClear(GL_COLOR_BUFFER_BIT);
        show_component();
        bullet->view();
        my_fighter->view();

        for(auto &&l : bullets_loc) {
            bullet->view_clone(l);
            l.sy+=0.0018;
        }

        glfwSwapBuffers(window1);
        glfwPollEvents();
        if(go_next->next_scene) {
            break;
        }
    }
    if(go_next->next_scene) {
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
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        bullets_loc.push_back(my_fighter->loc.clone());
        cout << bullets_loc.size() << endl;
    }
}
// void BattleScene::render(){}
BattleScene::~BattleScene() {}
