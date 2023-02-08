#include "SceneBase.hpp"
#include <GLFW/glfw3.h>

namespace sbfw {
extern int window_width, window_height;

namespace detail {
extern GLFWwindow *window;
}
namespace scene {
SceneBase *SceneBase::scb_ptr = nullptr;

void SceneBase::Start() {
    if(is_terminate_scene) {
        return;
    }
    if(window_name != "") {
        glfwSetWindowTitle(detail::window, window_name.c_str());
    }
    register_callbackfunc(*this, detail::window);
    next_scene = nullptr;
    InitAfterTransition();
    std::cout << "come new scene" << std::endl;
    // PNG画像が正しく表示される設定と透過される設定
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);

    while(!glfwWindowShouldClose(detail::window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Render();

        glfwSwapBuffers(detail::window);
        glfwPollEvents();

        if(next_scene != nullptr) {
            break;
        }
    }
    if(next_scene != nullptr) {
        // バツボタンを押してウィンドウを閉じるとnullptrなのでチェックが必要
        next_scene->Start();
    }
}

void SceneBase::ToRegularXY(double &x, double &y) {
    x /= window_width / 2;
    y /= window_height / 2;
    y = 1 - y;
    x = x - 1;
}

DataOf2D SceneBase::GetCursorRegularPos() {
    double x, y;
    glfwGetCursorPos(detail::window, &x, &y);
    ToRegularXY(x, y);
    return {float(x), float(y)};
}
void SceneBase::register_callbackfunc(SceneBase &sb, GLFWwindow *w) {
    scb_ptr = &sb;
    glfwSetMouseButtonCallback(w, mouse_func);
    glfwSetKeyCallback(w, key_func);
}

} // namespace scene
} // namespace sbfw