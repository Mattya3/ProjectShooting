#include <scene/SceneBase.hpp>

namespace sbfw {

namespace scene {

namespace detail {
static SceneBase *scb_ptr;
void mouse_func(GLFWwindow *pwin, int button, int action, int mods) {
    scb_ptr->mouse_button_callback(pwin, button, action, mods);
}
void key_func(GLFWwindow *window, int key, int scancode, int action, int mods) {
    scb_ptr->key_callback(window, key, scancode, action, mods);
}
void register_callbackfunc(SceneBase &sb, GLFWwindow *w) {
    scb_ptr = &sb;
    glfwSetMouseButtonCallback(w, mouse_func);
    glfwSetKeyCallback(w, key_func);
}

} // namespace detail
} // namespace scene
} // namespace sbfw
