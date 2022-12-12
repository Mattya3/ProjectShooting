#pragma once
#include <Setting.hpp>
#include <component/ButtonBase.hpp>
#include <component/NextSceneButton.hpp>

class Scene {
  private:
    bool mouse_down = false;

  protected:
    vector<ButtonBase *> btns;
    NextSceneButton *btn_next_scene;

  public:
    virtual void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                                       int mods) {
        double mousex, mousey;
        if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            mouse_down = true;
        } else if(mouse_down && button == GLFW_MOUSE_BUTTON_LEFT &&
                  action == GLFW_RELEASE) {
            mouse_down = false;
            glfwGetCursorPos(pwin, &mousex, &mousey);
            Setting::to_canonical_xy(mousex, mousey);
            for(auto &&btn : btns) {
                if(btn->valid_push_location(mousex, mousey)) {
                    btn->action_when_pushed();
                } else {
                    cout << mousex << ',' << mousey << "\n";
                }
            }
        }
    }
    virtual void key_callback(GLFWwindow *window, int key, int scancode,
                              int action, int mods) {}
    virtual void add_button(ButtonBase *btn) { btns.push_back(btn); }
    virtual void show_component() {
        for(auto &&e : btns) {
            e->button_view();
        }
    }
    virtual void render(GLFWwindow *window) {
        while(!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);

            show_component();
            // btn_func();
            if(btn_next_scene->is_pushed()) {}

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
};
