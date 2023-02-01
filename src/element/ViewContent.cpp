#include <element/ViewContent.hpp>

#include <element/button/Button.hpp>
#include <element/texture/ImageManager.hpp>
#include <element/texture/ImgUnit.hpp>

namespace sbfw {
texture::ImageManager ViewContent::img_manager;

ViewContent::ViewContent() {}

int ViewContent::add_image(string fname, DataOf2D pos, float scale) {
    // imgsは直接vectorを扱っているから冗長 ImgUnitを使う
    auto [id, len] = img_manager.provide_png(fname);
    texs.emplace_back(pos, id, len, scale);
    return texs.size() - 1;
}

int ViewContent::add_button(string fname, DataOf2D pos, float scale,
                            std::function<void(void)> action) {
    auto [id, len] = img_manager.provide_png(fname);
    texture::ImgUnit t(pos, id, len, scale);
    Button btn(t, action);
    btns.emplace_back(btn);
    return btns.size() - 1;
}
void ViewContent::change_image(int i, string fname) {
    auto [id, len] = img_manager.provide_png(fname);
    // texs[i] = texture::ImgUnit(texs[i].pos, id, len, texs[i].scale);
    texs[i].change(id, len);
}
void ViewContent::change_btn_image(int i, string fname) {
    auto [id, len] = img_manager.provide_png(fname);
    btns[i].tex.change(id, len);
}

} // namespace sbfw