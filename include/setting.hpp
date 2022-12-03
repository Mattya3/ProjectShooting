#pragma once
enum class sceneNumber {
    title,
    select_card,
    battle,
};
class Setting {
  private:
  public:
    Setting(/* args */);
    ~Setting();
    static sceneNumber scene_id;
    static constexpr int WINDOW_width = 800, WINDOW_height = 700;
    static inline void to_canonical_xy(double &x, double &y) {
        x /= WINDOW_width / 2;
        y /= WINDOW_height / 2;
        y = 1 - y;
        x = x - 1;
    }
};

Setting::Setting(/* args */) {}

Setting::~Setting() {}
