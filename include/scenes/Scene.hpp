#pragma once
#include <component/Button.hpp>
#include <utility.hpp>


class Scene {
  private:
  protected:
    vector<Button> btns;

  public:
    virtual void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                                       int mods) {}
    virtual void add_button() {}
};
