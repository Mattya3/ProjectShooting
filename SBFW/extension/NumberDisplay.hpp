#include <bits/stdc++.h>

#include "../sbfw.hpp"
#include "../unit.hpp"
namespace sbfw::ext {

class NumberDisplay {
  private:
    using Pdu = sbfw::texture::PartialDynamicUnit;
    template <class T> using vector = std::vector<T>;

  public:
    NumberDisplay() {
        for(size_t i = 0; i < 4; i++) {
            nums[i + 1] = Pdu(160 + i * 29, 0, 29, 42, atlas);
        }
        for(size_t i = 0; i < 4; i++) {
            nums[i + 5] = Pdu(160 + i * 29, 42, 29, 43, atlas);
        }
        for(size_t i = 0; i < 4; i++) {
            if(i == 0)
                nums[9] = Pdu(160 + i * 29, 86, 29, 43, atlas);
            else if(i == 1) {
                nums[0] = Pdu(160 + i * 29, 86, 29, 43, atlas);
            } else if(i == 2) {
                minus = Pdu(160 + i * 29, 86, 29, 43, atlas);
            } else if(i == 3) {
                dark_zero = Pdu(160 + i * 29, 86, 29, 43, atlas);
            }
        }
    }
    void Draw(int num, DataOf2D draw_start_pos, float ratio = 1.0f,
              int zero_fill_maxsize = -1) {
        Draw(std::to_string(num), draw_start_pos, ratio, zero_fill_maxsize);
    }
    void Draw(std::string const &numbers, DataOf2D start_pos,
              float ratio = 1.0f, int zero_fill_maxsize = -1) {
        auto sz = numbers.size();
        if(zero_fill_maxsize != -1 && sz < zero_fill_maxsize) {
            for(size_t i = 0; i < zero_fill_maxsize - sz; i++) {
                dark_zero.Draw(start_pos);
                start_pos.x += dark_zero.len.x + num_interval;
            }
        }
        for(auto &&e : numbers) {
            int i = e - '0';
            nums[i].Draw(start_pos);
            start_pos.x += nums[i].len.x + num_interval;
        }
    }

//   private:
    std::tuple<int, DataOf2D, int, int> atlas =
        sbfw::scene::SimpleScene::img_manager.ProvideImageGetWH("atlasv2.png");
    vector<Pdu> nums = vector<Pdu>(10);
    Pdu minus, dark_zero;
    const float num_interval = 0.065;
};
} // namespace sbfw::ext
