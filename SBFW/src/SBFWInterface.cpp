#include "SBFWInterface.hpp"
#include "SimpleScene.hpp"
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>

int sbfw::window_width = 800, sbfw::window_height = 700;

GLFWwindow *sbfw::detail::window = nullptr;

void sbfw::InitSBFW(int width, int height) {
    if(!glfwInit()) {
        exit(1);
    }
    window_width = width;
    window_height = height;
    detail::window =
        glfwCreateWindow(window_width, window_height, "test", NULL, NULL);

    if(!detail::window) {
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(detail::window);
} // #include "SBFW_HelperFunc.hpp"

void sbfw::TerminateSBFW() { glfwTerminate(); }
void sbfw::detail::CheckInited() {
    if(detail::window == nullptr) {
        std::cerr << "Not inited, Use sbfw::InitSBFW() first" << std::endl;
        exit(1);
    }
}
namespace sbfw {
namespace scene {
shared_ptr<SimpleScene> prepare_scene() {
    detail::CheckInited();
    return std::make_shared<SimpleScene>();
}

shared_ptr<SimpleScene> prepare_end() {

    detail::CheckInited();
    return shared_ptr<SimpleScene>();
}
} // namespace scene

} // namespace sbfw
