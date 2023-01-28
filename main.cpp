#include <scenes/Title_Scene.hpp>
#include <setting.hpp>
using namespace std;
#include "SBFW/sbfw.hpp"

int main() {
    GLFWwindow *window1, *window2;
    if(!glfwInit())
        return -1;

    window1 = glfwCreateWindow(Setting::WINDOW_width, Setting::WINDOW_height,
                               "Hello World", NULL, NULL);
    assert(window1);
    
    if(!window1) {
        glfwTerminate();
        return -1;
    }
    // 作成したウィンドウを，OpenGLの描画関数のターゲットに
    glfwMakeContextCurrent(window1);


    auto [title, select, game, score] = sbfw::scene::prepare_scenes<4>();

    Title_scene ts(window1);

    glfwTerminate();
    return 0;
}