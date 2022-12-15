#include <component/GridButtons.hpp>
#include <scenes/Scene.hpp>

#include <internal/card/CardHas.hpp>
#include <internal/card/ChangeStructure.hpp>

class SelectCardSub : Scene {
  private:
    /* data */
    bool *tm;
    GridButtons gb =
        GridButtons(Location(-0.9, -0.4, 1.8, 1.3), 3, 4, 0.05, 0.05);
    CardHas cardhas;
  public:
    void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                               int mods) override {
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
                }
            }
            gb.btns_valid(mousex, mousey);
        }
    }
    SelectCardSub(int struct_id, GLFWwindow *window);
    ~SelectCardSub();
};
