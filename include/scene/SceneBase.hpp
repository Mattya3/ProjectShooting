#pragma once
#include "ElemInfo.hpp"
#include "Setting.hpp"
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include <element/ViewContent.hpp>
namespace sbfw {

using std::shared_ptr;
namespace scene {
class SceneBase; // クラス前方宣言
// プロトタイプ宣言
namespace detail {
void mouse_func(GLFWwindow *pwin, int button, int action, int mods);
void key_func(GLFWwindow *window, int key, int scancode, int action, int mods);
void register_callbackfunc(SceneBase &sb, GLFWwindow *w);
} // namespace detail

class SceneBase {
  public:
    SceneBase() {}
    // static SceneBase make_end_scene() { return SceneBase(true); }

  private:
    SceneBase(bool b) : is_terminate_scene(b) {}

  public:
    inline ElemKey add_image(ElemInfo ei) {
        return ElemKey(ElemKey::ele_type::img,
                       contents.add_image(ei.img_fname, ei.pos, ei.scale));
    }
    inline ElemKey add_button(ElemInfo ei, std::function<void(void)> action) {
        return ElemKey(
            ElemKey::ele_type::btn,
            contents.add_button(ei.img_fname, ei.pos, ei.scale, action));
    }

    inline void change_image(ElemKey i, ElemInfo e) {
        if(i.e == ElemKey::ele_type::img)
            contents.change_image(i.key_id, e.img_fname);
        else if(i.e == ElemKey::ele_type::btn) {
            contents.change_btn_image(i.key_id, e.img_fname);
        }
    }
    inline ElemKey def_transtion_to(ElemInfo ei,
                                    shared_ptr<SceneBase> next_scene) {
        // 同じシーンへの遷移は不可能
        if(this == next_scene.get()) {
            std::cerr << "Can't go to same scene in def_transition_to()\n";
            std::cerr
                << "your code may be 'aiueo.def_transtion_to(el, aiueo);'??\n";
            exit(1);
        }
        return add_button(ei, [&]() { this->go_next_scene(next_scene); });
    }
    inline void set_window_name(std::string window_name_) {
        window_name = window_name_;
    }

  private:
    std::string window_name = "";

  protected:
    ViewContent contents;
    GLFWwindow *_win;

  public:
    void start(GLFWwindow *window) {
        if(is_terminate_scene) {
            return;
        }
        if(window_name != "") {
            glfwSetWindowTitle(window, window_name.c_str());
        }
        detail::register_callbackfunc(*this, window);
        next_scene = nullptr;
        _win = window;
        init();
        std::cout << "come new scene" << std::endl;
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);

        while(!glfwWindowShouldClose(window)) {
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            render();

            glfwSwapBuffers(window);
            glfwPollEvents();

            if(next_scene != nullptr) {
                break;
            }
        }
        if(next_scene != nullptr) {
            // バツボタンを押してウィンドウを閉じるとnullptrなのでcheckが必要
            next_scene->start(window);
        }
    }
    virtual void render() = 0;
    virtual void init() = 0;
    virtual void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                                       int mods) = 0;
    virtual void key_callback(GLFWwindow *window, int key, int scancode,
                              int action, int mods) = 0;

  private:
    shared_ptr<SceneBase> next_scene;
    bool is_terminate_scene = false;
    Setting setting;

  protected:
    void go_next_scene(shared_ptr<SceneBase> next_sc) { next_scene = next_sc; }
    DataOf2D get_cursor_pos() {
        double x, y;
        glfwGetCursorPos(_win, &x, &y);
        setting.to_canonical_xy(x, y);
        return {float(x), float(y)};
    }
};

using Scene_ptr = shared_ptr<SceneBase>;
} // namespace scene
} // namespace sbfw