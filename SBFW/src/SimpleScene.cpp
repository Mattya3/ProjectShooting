#include "SimpleScene.hpp"
#include <GLFW/glfw3.h>

namespace sbfw {

namespace scene {

void SimpleScene::mouse_button_callback(GLFWwindow *pwin, int button,
                                        int action, int mods) {
    double mousex, mousey;
    glfwGetCursorPos(pwin, &mousex, &mousey);
    ToRegularXY(mousex, mousey);

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        is1_clicked = true;
    } else if(is1_clicked && button == GLFW_MOUSE_BUTTON_LEFT &&
              action == GLFW_RELEASE) {
        is1_clicked = false;
        judege_btn_pushed(mousex, mousey);
    }
}
ElemKey SimpleScene::AddImage(ElemInfo ei) {
    auto [id, len] = img_manager.ProvideImage(ei.img_fname);
    texs.emplace_back(ei.pos, id, len, ei.scale);
    return ElemKey(ElemKey::ele_type::img, texs.size() - 1);
}
ElemKey SimpleScene::AddImage(std::string img_fname, DataOf2D pos,
                              float scale) {
    auto [id, len] = img_manager.ProvideImage(img_fname);
    texs.emplace_back(pos, id, len, scale);
    return ElemKey(ElemKey::ele_type::img, texs.size() - 1);
}

ElemKey SimpleScene::AddButton(ElemInfo ei, std::function<void(void)> action) {
    auto [id, len] = img_manager.ProvideImage(ei.img_fname);
    texture::ImgUnit t(ei.pos, id, len, ei.scale);
    Button btn(t, action);
    btns.emplace_back(btn);
    return ElemKey(ElemKey::ele_type::btn, btns.size() - 1);
}

void SimpleScene::ChangeImage(ElemKey i, ElemInfo e) {
    if(i.e == ElemKey::ele_type::img) {
        auto [id, len] = img_manager.ProvideImage(e.img_fname);
        texs[i.key_id].change(id, len);
    } else if(i.e == ElemKey::ele_type::btn) {
        auto [id, len] = img_manager.ProvideImage(e.img_fname);
        btns[i.key_id].tex.change(id, len);
    }
}
ElemKey SimpleScene::DefTranstionTo(ElemInfo ei,
                                    shared_ptr<SceneBase> next_scene) {
    // 同じシーンへの遷移は不可能
    if(this == next_scene.get()) {
        std::cerr << "Can't go to same scene in def_transition_to()\n";
        exit(1);
    }
    return AddButton(ei, [&]() { this->GoNextScene(next_scene); });
}
void SimpleScene::SetWindowName(std::string window_name_) {
    window_name = window_name_;
}
void SimpleScene::SetInitFunc(std::function<void(void)> f) {
    has_init_func = true;
    init_func = f;
}

} // namespace scene

} // namespace sbfw
