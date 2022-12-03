#include "src/Setting.cpp"
#include <Setting.hpp>
#include <bits/stdc++.h>
#include <component/Image.hpp>
#include <scenes/all_scene.hpp>

using namespace std;


int main() {
    GLFWwindow *window1, *window2;
    if(!glfwInit())
        return -1;

    // ウィンドウ作成
    window1 = glfwCreateWindow(Setting::WINDOW_width, Setting::WINDOW_height,
                               "Hello World", NULL, NULL);
    // window2 = glfwCreateWindow(400, 400, "window 2", NULL, NULL);

    if(!window1) {
        glfwTerminate();
        return -1;
    }
    // 作成したウィンドウを，OpenGLの描画関数のターゲットにする
    glfwMakeContextCurrent(window1);

    ChangeStructureView csv(window1);

    glfwTerminate();
    return 0;
}