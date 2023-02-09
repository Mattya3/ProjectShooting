#pragma once
#include "ElemInfo.hpp"
#include "ViewContent.hpp"
#include "math2D/DataOf2D.hpp"

#include <bits/stdc++.h>
#include "detail.hpp"
namespace sbfw {
using std::shared_ptr;

namespace scene {
class SceneBase {
  public:
    SceneBase() {}
    // static SceneBase make_end_scene() { return SceneBase(true); }

  private:
    SceneBase(bool b) : is_terminate_scene(b) {}

  public:
    void Start();

  protected:
    void GoNextScene(shared_ptr<SceneBase> next_sc) { next_scene = next_sc; }
    void ToRegularXY(double &x, double &y);

  protected:
    virtual void Render() = 0;
    virtual void InitAfterTransition() = 0;
    virtual void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                                       int mods) = 0;
    virtual void key_callback(GLFWwindow *window, int key, int scancode,
                              int action, int mods) = 0;

    DataOf2D GetCursorRegularPos();

  protected:
    GLFWwindow *_win;
    std::string window_name = "";

  private:
    shared_ptr<SceneBase> next_scene;
    bool is_terminate_scene = false;

  private:
    static SceneBase *scb_ptr;
    static void mouse_func(GLFWwindow *pwin, int button, int action, int mods) {
        scb_ptr->mouse_button_callback(pwin, button, action, mods);
    }
    static void key_func(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
        scb_ptr->key_callback(window, key, scancode, action, mods);
    }
    static void register_callbackfunc(SceneBase &sb, GLFWwindow *w);
};
} // namespace scene
} // namespace sbfw
