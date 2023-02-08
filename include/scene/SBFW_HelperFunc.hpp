#pragma once
#ifndef SBFW_HELPER_FUNC
#define SBFW_HELPER_FUNC
#include "SimpleScene.hpp"
#include "Setting.hpp"

// ヘルパ関数を定義する
namespace sbfw {

// void set_window_sz(int wwidth, int wheight);

// void set_window_sz(int wwidth, int wheight) {
//     setting.WINDOW_width = wwidth;
//     setting.WINDOW_height = wheight;
// }
namespace scene {
template <int n> std::array<shared_ptr<SimpleScene>, n> prepare_scenes() {
    std::array<shared_ptr<SimpleScene>, n> res;
    for(int i = 0; i < n; i++)
        res[i] = std::make_shared<SimpleScene>();
    return res;
}
auto prepare_scene() { return std::make_shared<SimpleScene>(); }
// T is derived SceneBase
template <class T, int n> std::array<shared_ptr<T>, n> prepare_scenes() {
    // if(static_pointer_cast<SceneBase>(shared_ptr<T>()) == nullptr) {
    //     std::cerr << "class not heritaging SceneBase is argument in "
    //                  "prepare_scenes()\n";
    //     exit(1);
    // }

    std::array<shared_ptr<T>, n> res;
    for(int i = 0; i < n; i++)
        res[i] = std::make_shared<T>();
    return res;
}
shared_ptr<SimpleScene> prepare_end() { return shared_ptr<SimpleScene>(); }

} // namespace scene

} // namespace sbfw
#endif
