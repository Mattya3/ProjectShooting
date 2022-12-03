#pragma once
#include <scenes/Scene.hpp>

class ChangeStructureView :public Scene {
  private:
  public:
    void add_button(Button *btn);
    void show_component();
    void mouse_button_callback(GLFWwindow *pwin, int button, int action, int mods);
    void render(GLFWwindow *window1);
    ChangeStructureView(GLFWwindow *window1);
    ~ChangeStructureView();
};
