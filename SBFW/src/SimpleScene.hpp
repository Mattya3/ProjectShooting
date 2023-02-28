#pragma once

#include <bits/stdc++.h>

#include "ImageManager.hpp"
#include "SceneBase.hpp"

#include "Button.hpp"
#include "ImgUnit.hpp"
#include "detail.hpp"

namespace sbfw {
extern texture::ImageManager img_manager;
template <class T> using sp = shared_ptr<T>;
namespace scene {
using std::tuple;
using std::vector;

/// @brief  ボタンと画像要素を貼り付ける事ができる画面クラス
class SimpleScene : public SceneBase {
  public:
    SimpleScene() {}
    /// @brief 不動の画像を画面に追加する
    /// @param img_fname 画像のファイル名
    /// @param pos 画像の設置位置
    /// @param scale 画像の拡大率
    /// @return ElemKey あとから画像を差し替える時にこれを指定する
    ElemKey AddImage(std::string img_fname, DataOf2D pos, float scale = 1.0);
    /// @brief 不動の画像を画面に追加する
    /// @param ei 画像のファイル名、設置位置、拡大率の情報を含む構造体
    /// @return ElemKey あとから画像を差し替える時にこれを指定する
    ElemKey AddImage(ElemInfo ei);
    ElemKey AddButton(ElemInfo ei, std::function<void(void)> action);
    void ChangeImage(ElemKey i, ElemInfo e);
    ElemKey DefTranstionTo(ElemInfo ei, shared_ptr<SceneBase> next_scene);
    void SetWindowName(std::string window_name_);
    void SetInitFunc(std::function<void(void)> f);

  private:
    bool is1_clicked = false;
    std::function<void(void)> init_func;
    bool has_init_func = false;

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

    void InitAfterTransition() override {
        ResetAllButton();
        if(has_init_func)
            init_func();
    }
    void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                               int mods) override;
    void key_callback(GLFWwindow *window, int key, int scancode, int action,
                      int mods) override {}

  protected:
    vector<Button> btns;
    vector<texture::ImgUnit> texs;

  private:
    void ResetAllButton() {
        for(auto &&e : btns) {
            e.Reset();
        }
    }

  public:
    static shared_ptr<SimpleScene> __ProgramTerminateScene() {
        auto s = std::make_shared<SimpleScene>();
        s->is_terminate_scene = true;
        return s;
    }
};
extern shared_ptr<SimpleScene> program_terminate;
} // namespace scene

} // namespace sbfw
