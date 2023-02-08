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
    SimpleScene() {}

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
    inline void draw_btn_touched() {
        auto [mousex, mousey] = get_cursor_pos();
        for(auto &&btn : contents.get_btns()) {
            if(btn.valid_push_location(mousex, mousey)) {
                btn.action_when_cursor_touched();
            }
        }
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
        draw_btn_touched();
        layer_front();
    }

    void init() override {}
    // イベントが起きたときしか呼び出されない無いっぽい
    // touchedはrenderで判定しよう
    Setting setting;
    inline void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                                      int mods) override {
        double mousex, mousey;
        glfwGetCursorPos(pwin, &mousex, &mousey);
        setting.to_canonical_xy(mousex, mousey);

        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            is1_clicked = true;
        } else if(is1_clicked && button == GLFW_MOUSE_BUTTON_LEFT &&
                  action == GLFW_RELEASE) {
            is1_clicked = false;
            judege_btn_pushed(mousex, mousey);
        }
    }
    inline void key_callback(GLFWwindow *window, int key, int scancode,
                             int action, int mods) override {}
};

} // namespace scene

} // namespace sbfw

#include <scene/SBFW_HelperFunc.hpp>