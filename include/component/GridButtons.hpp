#pragma once
#include <component/Button_ONOF.hpp>
#include <component/Location.hpp>

class GridButtons {
  private:
    int xn, yn; // 横に何個並べるか 縦に何個並べるか
    double x_interval, y_interval;         // ボタン同士の間隔
    Location draw_domain;                  // グリッドを描画する領域
    vector<vector<Button_ONOF *>> buttons; // グリッドにある各ボタン
    int selected_x = -1, selected_y = -1;  // 選ばれたカードの位置

  public:
    GridButtons(Location draw_domain, int number_xbtn, int number_ybtn,
                double x_interval, double y_interval);
    ~GridButtons();
    void view();
    void btns_valid(double x, double y);

    inline int get_selected() { return card_id_of_index(); }

  private:
    inline int card_id_of_index() { return selected_x + xn * selected_y; }
};
