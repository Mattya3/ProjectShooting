#pragma once
/**
 * SimpleSceneを継承した独自のSceneクラスを定義するためのヘッダ
 * 隠蔽を維持した上でImgUnitを使うことができる。
 * このヘッダをincludeし、SimpleSceneを継承したクラスを定義すること。
 */
#include "include/scene/SimpleScene.hpp"

/** example template
class YourScene : sbfw::scene::SimpleScene {
  protected:
    void layer_front() override {}
    void layer_back() override {}
    void init() override {}
    inline void key_callback(GLFWwindow *window, int key, int scancode,
                             int action, int mods) override {}
}
 */