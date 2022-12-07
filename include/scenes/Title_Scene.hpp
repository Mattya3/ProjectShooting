#pragma once
#include <scenes/Scene.hpp>

class Title_scene : public Scene {
  private:
  public:
    void show_component() {
        for(auto &&e : btns) {
            e->button_view();
        }
    }
    void render(GLFWwindow *window1);
    Title_scene(GLFWwindow *window1);
    ~Title_scene();
};
