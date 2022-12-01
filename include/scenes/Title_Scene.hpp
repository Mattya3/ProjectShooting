#pragma once
#include <scenes/Scene.hpp>

class Title_scene : public Scene {
  private:
  public:
    void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                               int mods) {
        double mousex, mousey;
        glfwGetCursorPos(pwin, &mousex, &mousey);
        to_canonical_xy(mousex, mousey);
        for(auto &&btn : btns) {
            if(btn.valid_push_location(mousex, mousey)) {
                btn.action_when_pushed();
            } else {
                cout << "no valid"
                     << "\n";
                cout << mousex << ',' << mousey << "\n";
            }
        }
    }
    void add_button(Button btn) { btns.push_back(btn); }
    void show_component() {
        for(auto &&e : btns) {
            e.button_view();
        }
    }
    Title_scene();
    ~Title_scene();
};
