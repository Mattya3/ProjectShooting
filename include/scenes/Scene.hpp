#pragma once
#include <Setting.hpp>
#include <component/ButtonBase.hpp>
#include <component/NextSceneButton.hpp>
/**
 * @brief
 * 全てのシーンの親クラス
 **/
class Scene {
  private:
    bool mouse_down = false;

  protected:
    vector<ButtonBase *> btns;
    NextSceneButton *btn_next_scene;// スマートポインタに！
    virtual void render() {}

  public:
    virtual void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                                       int mods);
    virtual void key_callback(GLFWwindow *window, int key, int scancode,
                              int action, int mods) {}
    virtual inline void add_button(ButtonBase *btn) { btns.push_back(btn); }
    virtual void show_component() {
        for(auto &&e : btns) {
            e->button_view();
        }
    }
};
