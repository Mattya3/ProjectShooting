#pragma once
class Setting {
  private:
  public:
    static const int sceneNumber_title = 1, sceneNumber_select_card = 2,
                     sceneNumber_battle = 3;
    Setting(/* args */);
    ~Setting();
    static const int WINDOW_width = 800, WINDOW_height = 700;
    static inline void to_canonical_xy(double &x, double &y) {
        x /= WINDOW_width / 2;
        y /= WINDOW_height / 2;
        y = 1 - y;
        x = x - 1;
    }
    class imgData {
        constexpr static int back_arrow = 3;
    };
};
