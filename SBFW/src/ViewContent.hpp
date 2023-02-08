#pragma once
#include "math2D/DataOf2D.hpp"

#include <bits/stdc++.h>

#include "Button.hpp"
#include "ImageManager.hpp"
#include "ImgUnit.hpp"

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
    static texture::ImageManager img_manager;

  public:
    explicit ViewContent();
    int AddImage(string fname, DataOf2D pos, float scale = 1.0f);
    int AddButton(string fname, DataOf2D pos, float scale,
                  std::function<void(void)> action);
    void ChangeImage(int i, string fname);
    void ChangeBtnImage(int i, string fname);

  private:
    vector<Button> btns;
    vector<texture::ImgUnit> texs;

  public:
    vector<texture::ImgUnit> &_get_imgs() { return texs; }
    auto &get_btns() { return btns; }
};
} // namespace sbfw
