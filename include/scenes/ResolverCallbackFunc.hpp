#include <scenes/Scene.hpp>

// GLFWにおいてコールバック関数としてインスタンスメソッドを登録できない
// 間に静的関数をかませることで解決する。
// シーンの各種マウスキー入力監視関数をコールバック登録する

static Scene *sc_ptr;
class register_callback_resolver {
  private:
    static void mouse_func(GLFWwindow *pwin, int button, int action, int mods) {
        sc_ptr->mouse_button_callback(pwin, button, action, mods);
    }
    static void key_func(GLFWwindow *window, int key, int scancode, int action,
                         int mods) {
        sc_ptr->key_callback(window, key, scancode, action, mods);
    }

  public:
    static void init(Scene &sc, GLFWwindow *pwin) {
        sc_ptr = &sc;
        glfwSetMouseButtonCallback(pwin, mouse_func);
        glfwSetKeyCallback(pwin, key_func);
    }
};