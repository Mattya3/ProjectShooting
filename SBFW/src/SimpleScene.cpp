#include "SimpleScene.hpp"
#include <GLFW/glfw3.h>
namespace sbfw {
namespace scene {
void SimpleScene::mouse_button_callback(GLFWwindow *pwin, int button,
                                        int action, int mods) {
    double mousex, mousey;
    glfwGetCursorPos(pwin, &mousex, &mousey);
    ToRegularXY(mousex, mousey);

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        is1_clicked = true;
    } else if(is1_clicked && button == GLFW_MOUSE_BUTTON_LEFT &&
              action == GLFW_RELEASE) {
        is1_clicked = false;
        judege_btn_pushed(mousex, mousey);
    }
}
} // namespace scene

} // namespace sbfw
