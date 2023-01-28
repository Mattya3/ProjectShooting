#pragma once
#include "ElemInfo.hpp"
#include <GLFW/glfw3.h>
#include <element/ViewContent.hpp>
#include <bits/stdc++.h>
namespace sbfw{

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
    inline int add_image(ElemInfo ei) {
        return contents.add_image(ei.img_fname, ei.pos, ei.scale);
    }
    inline int add_button(ElemInfo ei, std::function<void(void)> action) {
        return contents.add_button(ei.img_fname, ei.pos, ei.scale, action);
    }

      

    inline void change_image(int i, ElemInfo e) {
        contents.change_image(i, e.img_fname);
    }
    inline void def_transtion_to(ElemInfo ei,
                                 shared_ptr<SceneBase> next_scene) {
        if(this == next_scene.get()) {
            std::cerr << "Can't go to same scene in def_transition_to()\n";
            std::cerr
                << "your code may be 'aiueo.def_transtion_to(el, aiueo);'??\n";
            exit(1);
        }
        contents.add_button(ei.img_fname, ei.pos, ei.scale,
                            [&]() { this->go_next_scene(next_scene); });
    }

  protected:
    ViewContent contents;

  public:
    void start(GLFWwindow *window) {
        if(is_terminate_scene) {
            return;
        }
        detail::register_callbackfunc(*this, window);
        next_scene = nullptr;
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

  protected:
    void go_next_scene(shared_ptr<SceneBase> next_sc) { next_scene = next_sc; }
};

using Scene_ptr = shared_ptr<SceneBase>;
} // namespace scene
} // namespace sbfw
