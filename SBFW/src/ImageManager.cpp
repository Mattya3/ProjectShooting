#include "ImageManager.hpp"
#include "lodepng/lodepng.h"
#include "math2D/DataOf2D.hpp"

#include <GLFW/glfw3.h>
#include <filesystem>
#include <string>

namespace sbfw {
extern int window_width, window_height;

namespace texture {
std::pair<int, DataOf2D> ImageManager::ProvideImage(string const &fname) {
    auto [bind_id, len, w, h] = ProvideImageGetWH(fname);
    return {bind_id, len};
}
std::tuple<int, DataOf2D, int, int>
ImageManager::ProvideImageGetWH(string const &fname) {
    using std::filesystem::current_path;
    string filename = (current_path() / std::filesystem::path("img/" + fname))
                          .string()
                          .c_str();

    if(!std::filesystem::exists(filename)) {
        std::cerr << "Not found " << filename << '\n';
        exit(1);
    }
    if(int bind_id = IsAlreadyLoaded(fname); bind_id != -1) {
        // printf("%s has loaded already as %d, (w, h) = (%f, %f)\n",
        // fname.c_str(),
        //        bind_id, len_data[bind_id].x, len_data[bind_id].y);
        return {bind_id, len_data[bind_id], len_data_un_reg[bind_id].first,
                len_data_un_reg[bind_id].second};
    } else {
        ++id;
        std::cout << fname << " as  " << id << std::endl;

        loaded_pngs.emplace(fname, id);
        auto [w, h] = LoadPng(filename, id);
        len_data_un_reg.emplace_back(w, h);
        DataOf2D t = GetRegularLen(w, h);
        len_data.emplace_back(t);
        // printf("%s is loading as %d, (w, h) = (%f, %f)\n", fname.c_str(), id,
        // t.x, t.y);
        return {id, t, w, h};
    }
}

int ImageManager::IsAlreadyLoaded(string const &fname) {
    auto it = loaded_pngs.find(fname);
    if(it != loaded_pngs.end()) {
        return it->second;
    } else {
        return -1;
    }
}
inline DataOf2D ImageManager::GetRegularLen(uint32_t w, uint32_t h) {
    return {w / float(window_width) * 2.0f, h / float(window_height) * 2.0f};
}
std::pair<int, int> ImageManager::LoadPng(std::string const &fullpath_fname,
                                          int id) {
    using ubyte_t = unsigned char;

    unsigned int width, height;
    std::vector<ubyte_t> data;

    unsigned error = lodepng::decode(data, width, height, fullpath_fname);

    if(error != 0) {
        std::cout << "Deconding PNG, error " << error << ": "
                  << lodepng_error_text(error) << std::endl;
        exit(1);
    }
    // テクスチャへの登録
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, &data[0]);
    return {width, height};
}
} // namespace texture

} // namespace sbfw