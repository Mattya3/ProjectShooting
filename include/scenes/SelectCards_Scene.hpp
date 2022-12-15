#pragma once
#include <scenes/Scene.hpp>

class SelectCards_Scene : public Scene {
    using Scene::Scene;
    
  private:
    bool is_no_subWindow = true;

  public:
    void show_component();
    void render();
    SelectCards_Scene(GLFWwindow *window1);
    ~SelectCards_Scene();
};
