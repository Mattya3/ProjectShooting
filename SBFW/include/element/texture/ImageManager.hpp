#include "PngData.hpp"
#include <bits/stdc++.h>
#include <filesystem>
namespace sbfw {

namespace texture {

class ImageManager {
  public:
    ImageManager() {}

  private:
    int id = 0;
    std::unordered_map<std::string, int> loaded_pngs;
    PngData pngdata;

  public:
    std::pair<int, DataOf2D> provide_png(std::string fname);
} img_manager;

} // namespace texture

} // namespace sbfw
