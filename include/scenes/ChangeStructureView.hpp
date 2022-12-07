#pragma once
#include <scenes/Scene.hpp>

class ChangeStructureView : public Scene {
  private:
    bool is_no_subWindow=true;

  public:
    void show_component();
    void render();
    ChangeStructureView(GLFWwindow *window1);
    ~ChangeStructureView();
};
