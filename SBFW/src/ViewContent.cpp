#include "ViewContent.hpp"

#include "Button.hpp"
#include "ImageManager.hpp"
#include "ImgUnit.hpp"

namespace sbfw {
texture::ImageManager ViewContent::img_manager;

ViewContent::ViewContent() {}

int ViewContent::AddImage(string fname, DataOf2D pos, float scale) {
    // imgsは直接vectorを扱っているから冗長 ImgUnitを使う
    auto [id, len] = img_manager.ProvideImage(fname);
    texs.emplace_back(pos, id, len, scale);
    return texs.size() - 1;
}

int ViewContent::AddButton(string fname, DataOf2D pos, float scale,
                            std::function<void(void)> action) {
    auto [id, len] = img_manager.ProvideImage(fname);
    texture::ImgUnit t(pos, id, len, scale);
    Button btn(t, action);
    btns.emplace_back(btn);
    return btns.size() - 1;
}
void ViewContent::ChangeImage(int i, string fname) {
    auto [id, len] = img_manager.ProvideImage(fname);
    // texs[i] = texture::ImgUnit(texs[i].pos, id, len, texs[i].scale);
    texs[i].change(id, len);
}
void ViewContent::ChangeBtnImage(int i, string fname) {
    auto [id, len] = img_manager.ProvideImage(fname);
    btns[i].tex.change(id, len);
}

} // namespace sbfw
