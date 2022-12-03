#pragma once
#include <Setting.hpp>
#include <component/Button.hpp>

class Scene {
  private:
  protected:
    vector<Button*> btns;

  public:
    virtual void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                                       int mods) {}
    virtual void add_button(Button *btn){}
    virtual void render(){}
};
