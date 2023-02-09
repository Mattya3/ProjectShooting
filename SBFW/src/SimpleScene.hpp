#pragma once

#include <bits/stdc++.h>

#include "SceneBase.hpp"
#include "ImageManager.hpp"

#include "Button.hpp"
#include "ImgUnit.hpp"
#include "detail.hpp"

namespace sbfw {

template <class T> using sp = shared_ptr<T>;
namespace scene {
using std::tuple;
using std::vector;

/// @brief  ボタンと画像要素を貼り付ける事ができる画面クラス
class SimpleScene : public SceneBase {
  public:
    SimpleScene() {}
    ElemKey AddImage(ElemInfo ei);
    ElemKey AddButton(ElemInfo ei, std::function<void(void)> action);
    void ChangeImage(ElemKey i, ElemInfo e);
    ElemKey DefTranstionTo(ElemInfo ei, shared_ptr<SceneBase> next_scene);
    void SetWindowName(std::string window_name_);

  private:
    bool is1_clicked = false;
    inline void judege_btn_pushed(float x, float y) {
        try {
            for(auto &&btn : btns) {
                if(btn.valid_push_location(x, y)) {
                    btn.action_when_pushed();
                }
            }
        } catch(const std::exception &e) { std::cerr << e.what() << '\n'; }
    }
    inline void draw_btn_touched() {
        auto [mousex, mousey] = GetCursorRegularPos();
        for(auto &&btn : btns) {
            if(btn.valid_push_location(mousex, mousey)) {
                btn.action_when_cursor_touched();
            }
        }
    }
    virtual void layer_front() {}
    virtual void layer_back() {}

    inline void Render() override final {
        layer_back();
        for(auto &&e : texs) {
            e.Draw();
        }
        for(auto &&btn : btns) {
            btn.draw();
        }
        draw_btn_touched();
        layer_front();
    }

    void InitAfterTransition() override {}
    void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                               int mods) override;
    void key_callback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) override {}

  protected:
    vector<Button> btns;
    vector<texture::ImgUnit> texs;

    static texture::ImageManager img_manager;
};

} // namespace scene

} // namespace sbfw
