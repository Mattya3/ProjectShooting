#include "SBFWInterface.hpp"
#include "SimpleScene.hpp"
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>

int sbfw::window_width = 800, sbfw::window_height = 700;

GLFWwindow *sbfw::detail::window = nullptr;
sbfw::texture::ImageManager sbfw::img_manager = sbfw::texture::ImageManager();

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
DataOf2D sbfw::ToRegularXYpos(unsigned x, unsigned y) {
    float tx = x, ty = y;
    tx /= sbfw::window_width / 2;
    ty /= sbfw::window_height / 2;
    ty = 1 - ty;
    tx = tx - 1;
    return {tx, ty};
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
