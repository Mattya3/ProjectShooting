#pragma once
#include <bits/stdc++.h>

#include "../sbfw.hpp"
#include "../unit.hpp"
namespace sbfw::ext {

/// @brief 数字を指定した位置に表示するクラス
class NumberDisplay {
  private:
    using Tex = sbfw::texture::PartialDynamicUnit;
    template <class T> using vector = std::vector<T>;

  public:
    NumberDisplay() {
        for(size_t i = 0; i < 4; i++) {
            nums[i + 1] = Tex(160 + i * 29, 0, 29, 42, atlas);
        }
        for(size_t i = 0; i < 4; i++) {
            nums[i + 5] = Tex(160 + i * 29, 42, 29, 43, atlas);
        }
        for(size_t i = 0; i < 4; i++) {
            if(i == 0)
                nums[9] = Tex(160 + i * 29, 86, 29, 43, atlas);
            else if(i == 1) {
                nums[0] = Tex(160 + i * 29, 86, 29, 43, atlas);
            } else if(i == 2) {
                minus = Tex(160 + i * 29, 86, 29, 43, atlas);
            } else if(i == 3) {
                dark_zero = Tex(160 + i * 29, 86, 29, 43, atlas);
            }
        }
    }

    /// @brief 数字を桁数指定して描画する
    /// @param num 描画したい数字(int)
    /// @param draw_start_pos 描画の開始位置つまり最も左の桁の座標
    /// @param scale 拡大率
    /// @param digit_num ゼロ埋め桁数
    inline void Draw(int num, DataOf2D draw_start_pos, float scale = 1.0f,
                     int digit_num = 5) {
        Draw(std::to_string(num), draw_start_pos, scale, digit_num);
    }
    /// @brief 数字を桁数指定して描画する
    /// @param num 描画したい数字(string)
    /// @param draw_start_pos 描画の開始位置つまり最も左の桁の座標
    /// @param scale 拡大率
    /// @param digit_num ゼロ埋め桁数
    inline void Draw(std::string const &numbers, DataOf2D start_pos,
                     float scale = 1.0f, int digit_num = 5,
                     bool is_zero_fill = true) {
        auto sz = numbers.size();
        if(is_zero_fill && sz < digit_num) {
            for(size_t i = 0; i < digit_num - sz; i++) {
                dark_zero.Draw(start_pos, scale);
                start_pos.x += 0.07f * scale;
            }
        }
        // 数字を描画
        for(auto &&e : numbers) {
            int i = (e - '0');
            nums[i].Draw(start_pos, scale);
            start_pos.x += 0.07f * scale;
        }
    }

  private:
    std::tuple<int, DataOf2D, int, int> atlas =
        sbfw::img_manager.ProvideImageGetWH("atlasv2.png");
    vector<Tex> nums = vector<Tex>(10);
    Tex minus, dark_zero;
    const float num_interval = 0.0065;
};
} // namespace sbfw::ext
