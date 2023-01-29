#pragma once
#include <bits/stdc++.h>

#include <GLFW/glfw3.h>

#include <DataOf2D.hpp>
#include <lodepng.h>
#include <scene/Setting.hpp>

namespace sbfw {

namespace texture {
class PngData {
  private:
    using ubyte_t = unsigned char;
    std::vector<std::vector<ubyte_t>> imgs_data; // 画像のデータ
    std::vector<DataOf2D> len_data;

  public:
    PngData() : imgs_data(50), len_data(50) {}
    DataOf2D get_len(int bind_id) { return len_data[bind_id]; }
    DataOf2D make_len(uint32_t w, uint32_t h) {
        return {w / float(setting.WINDOW_width) * 2.0f,
                h / float(setting.WINDOW_height) * 2.0f};
    }
    void load_png(std::string const &fullpath_fname, int id) {
        unsigned int width, height;
        std::vector<ubyte_t> data;

        unsigned error = lodepng::decode(data, width, height, fullpath_fname);

        if(error != 0) {
            std::cout << "Deconding PNG, error " << error << ": "
                      << lodepng_error_text(error) << std::endl;
            exit(1);
        }
        len_data[id] = make_len(width, height);
        // テクスチャへの登録
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, &data[0]);
    }
};

} // namespace texture

} // namespace sbfw
