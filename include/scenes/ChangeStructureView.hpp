#pragma once
#include <component/Button.hpp>
#include <scenes/Scene.hpp>

class ChangeStructureView : Scene {
  private:
  public:
    void add_button(Button btn);
    void show_component();
    void mouse_button_callback(GLFWwindow *pwin, int button, int action, int mods);
    ChangeStructureView(/* args */);
    ~ChangeStructureView();
};
