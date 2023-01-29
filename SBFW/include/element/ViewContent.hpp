#pragma once
#include <DataOf2D.hpp>
#include <bits/stdc++.h>

// ここは前方宣言にしたい
#include <element/button/Button.hpp>
#include <element/texture/ImgUnit.hpp>

namespace sbfw {

class Button;
namespace texture {
class ImgUnit;
} // namespace texture

class ViewContent {
  private:
    using string = std::string;
    template <class T> using vector = std::vector<T>;
    template <class T> using sp = std::shared_ptr<T>;

  public:
    ViewContent();
    int add_image(string fname, DataOf2D pos, float scale = 1.0f);
    int add_button(string fname, DataOf2D pos, float scale,
                   std::function<void(void)> action);
    void change_image(int i, string fname);
    void change_btn_image(int i, string fname);

  private:
    vector<Button> btns;
    vector<texture::ImgUnit> texs;

  public:
    vector<texture::ImgUnit> &_get_imgs() { return texs; }
    auto &get_btns() { return btns; }
};

} // namespace sbfw
