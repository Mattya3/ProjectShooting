#pragma once
#ifndef SBFW_HELPER_FUNC
#define SBFW_HELPER_FUNC
#include "SimpleScene.hpp"
#include "detail.hpp"
namespace sbfw {
void InitSBFW(int width, int height);
void TerminateSBFW();
DataOf2D ToRegularXYpos(unsigned x, unsigned y);
namespace scene {

shared_ptr<SimpleScene> prepare_scene();
shared_ptr<SimpleScene> prepare_end();

template <int n> std::array<shared_ptr<SimpleScene>, n> prepare_scenes() {
    detail::CheckInited();
    std::array<shared_ptr<SimpleScene>, n> res;
    for(int i = 0; i < n; i++)
        res[i] = std::make_shared<SimpleScene>();
    return res;
}

// T is derived SceneBase
template <class T, int n> std::array<shared_ptr<T>, n> prepare_scenes() {
    detail::CheckInited();
    std::array<shared_ptr<T>, n> res;
    for(int i = 0; i < n; i++)
        res[i] = std::make_shared<T>();
    return res;
}
} // namespace scene

} // namespace sbfw
#endif
