#include <scenes/Scene.hpp>


void Scene::mouse_button_callback(GLFWwindow *pwin, int button, int action,
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
                    // cout << mousex << ',' << mousey << "\n";
                }
            }
        }
    }