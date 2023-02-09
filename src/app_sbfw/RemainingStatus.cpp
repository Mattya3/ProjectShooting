#include <app_sbfw/RemainingStatus.hpp>

void RemainingStatus::Draw(int now_stock) {
    DataOf2D p = view_start_point;
    // imgをobject_num個全部表示する
    for(int i = 0; i < object_num; i++) {
        img.Draw(p);
        p += {img.len.x + interval, 0};
    }
    // 座標の用意
    float left = view_start_point.x - img.len.x/2;
    float lenx_drawing = img.len.x * object_num;
    float right = left + lenx_drawing;
    float begin_hide_x =
        left + float(now_stock) / float(max_stock) * lenx_drawing;
    // 右側から隠す
    draw::RectFilled(begin_hide_x, right, view_start_point.y + img.len.y / 2,
                     view_start_point.y - img.len.y / 2, {0.0, 1.0, 0.0});
}