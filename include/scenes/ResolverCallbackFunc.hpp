#include <scenes/Scene.hpp>

static Scene *sc_ptr;
class register_callback_resolver {
  private:
    static void mouse_func(GLFWwindow *pwin, int button, int action, int mods) {
        sc_ptr->mouse_button_callback(pwin, button, action, mods);
    }

  public:
    static void init(Scene &sc, GLFWwindow *pwin) {
        sc_ptr = &sc;
        glfwSetMouseButtonCallback(pwin, mouse_func);
    }
};