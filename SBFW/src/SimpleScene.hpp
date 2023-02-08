#pragma once

#include <bits/stdc++.h>

#include "SceneBase.hpp"
#include "ViewContent.hpp"

#include "Button.hpp"
#include "ImgUnit.hpp"
#include "Setting.hpp"
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
    inline ElemKey AddImage(ElemInfo ei) {
        return ElemKey(ElemKey::ele_type::img,
                       contents.AddImage(ei.img_fname, ei.pos, ei.scale));
    }
    inline ElemKey AddButton(ElemInfo ei, std::function<void(void)> action) {
        return ElemKey(
            ElemKey::ele_type::btn,
            contents.AddButton(ei.img_fname, ei.pos, ei.scale, action));
    }

    inline void ChangeImage(ElemKey i, ElemInfo e) {
        if(i.e == ElemKey::ele_type::img)
            contents.ChangeImage(i.key_id, e.img_fname);
        else if(i.e == ElemKey::ele_type::btn) {
            contents.ChangeBtnImage(i.key_id, e.img_fname);
        }
    }
    inline ElemKey DefTranstionTo(ElemInfo ei,
                                  shared_ptr<SceneBase> next_scene) {
        // 同じシーンへの遷移は不可能
        if(this == next_scene.get()) {
            std::cerr << "Can't go to same scene in def_transition_to()\n";
            exit(1);
        }
        return AddButton(ei, [&]() { this->GoNextScene(next_scene); });
    }
    inline void SetWindowName(std::string window_name_) {
        window_name = window_name_;
    }

  protected:
    ViewContent contents;

  private:
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
        auto [mousex, mousey] = GetCursorRegularPos();
        for(auto &&btn : contents.get_btns()) {
            if(btn.valid_push_location(mousex, mousey)) {
                btn.action_when_cursor_touched();
            }
        }
    }
    virtual void layer_front() {}
    virtual void layer_back() {}

    inline void Render() override final {
        layer_back();
        for(auto &&e : contents._get_imgs()) {
            e.Draw();
        }
        for(auto &&btn : contents.get_btns()) {
            btn.draw();
        }
        draw_btn_touched();
        layer_front();
    }

    void InitAfterTransition() override {}
    // イベントが起きたときしか呼び出されない無いっぽい
    // touchedはrenderで判定しよう
    void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                               int mods) override;
    void key_callback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) override {}
};

} // namespace scene

} // namespace sbfw
