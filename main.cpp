#include <Setting.hpp>
#include <scenes/Title_Scene.hpp>

using namespace std;

int main() {
    GLFWwindow *window1, *window2;
    if(!glfwInit())
        return -1;

    window1 = glfwCreateWindow(Setting::WINDOW_width, Setting::WINDOW_height,
                               "Hello World", NULL, NULL);

    if(!window1) {
        glfwTerminate();
        return -1;
    }
    // 作成したウィンドウを，OpenGLの描画関数のターゲットに
    glfwMakeContextCurrent(window1);

    Title_scene ts(window1);

    glfwTerminate();
    return 0;
}