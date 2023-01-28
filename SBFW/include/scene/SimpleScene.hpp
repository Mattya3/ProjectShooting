#pragma once

#include <bits/stdc++.h>

#include <element/ViewContent.hpp>
#include <scene/SceneBase.hpp>

#include <element/button/Button.hpp>
#include <element/texture/ImgUnit.hpp>
#include <scene/Setting.hpp>

namespace sbfw {

template <class T> using sp = shared_ptr<T>;
namespace scene {
using std::tuple;
using std::vector;

// ボタンを有するScene
class SimpleScene : public SceneBase {
  public:
    SimpleScene() {
        // vector<pair<shared_ptr<ButtonBase>, Scene_ptr>> content;
        // 上記を引数で貰えれば任意のボタンとシーン遷移ができるシーンが作れる。
        // auto btn = make_shared<NextSceneButton>(-0.9, -0.9, 0.49, 0.49);
        // btn->set_color(0.5, 0.5, 0.0);
        // auto back_arrow = make_shared<PngTexture>(
        //     "test_img/back.png", Location(-0.9, -0.9, 0.49, 0.49));
        // content.emplace_back(btn, back_arrow, nullptr);
    }

  protected:
    bool is1_clicked = false;
    inline void judege_btn_pushed(float x, float y) {
        try {
            for(auto &&btn : contents.get_btns()) {
                if(btn.valid_push_location(x, y)) {
                    btn.action_when_pushed();
                }
            }
        } catch(const std::exception &e) { std::cerr << e.what() << '\n'; }
    }
    virtual void layer_front() {}
    virtual void layer_back() {}

    inline void render() override final {
        layer_back();
        for(auto &&e : contents._get_imgs()) {
            e.view();
        }
        for(auto &&btn : contents.get_btns()) {
            btn.draw();
            // if(btn.is_pushed()) {
            //     btn.action_when_pushed();
            // }
        }
        layer_front();
    }

    void init() override {}
    inline void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                                      int mods) override {
        double mousex, mousey;
        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            is1_clicked = true;
        } else if(is1_clicked && button == GLFW_MOUSE_BUTTON_LEFT &&
                  action == GLFW_RELEASE) {
            is1_clicked = false;
            glfwGetCursorPos(pwin, &mousex, &mousey);
            setting.to_canonical_xy(mousex, mousey);
            judege_btn_pushed(mousex, mousey);
        }
    }
    inline void key_callback(GLFWwindow *window, int key, int scancode,
                             int action, int mods) override {}
};

} // namespace scene

} // namespace sbfw

#include <scene/SBFW_HelperFunc.hpp>