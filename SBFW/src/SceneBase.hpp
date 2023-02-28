#pragma once
#include "ElemInfo.hpp"
#include "math2D/DataOf2D.hpp"

#include "detail.hpp"
#include <bits/stdc++.h>
namespace sbfw {
using std::shared_ptr;

} // namespace sbfw

/// @brief GLFWのWindow制御を隠蔽するクラス コールバック登録も行う
namespace sbfw::scene {

class SceneBase {
  public:
    SceneBase() {}

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
    int frame_cnt;
    float elapsed_time_this_scene;
    const int frame_per_sec = 60;

  protected:
    inline int GetFrameCnt() { return frame_cnt; }
    inline float GetElapsedTime() { return elapsed_time_this_scene; }

  private:
    shared_ptr<SceneBase> next_scene;

  protected:
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
} // namespace sbfw::scene
