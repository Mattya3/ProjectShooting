#include <DataOf2D.hpp>

template <class T> void DrawRowImg(T img, DataOf2D draw_start_pos) {
    // imgをobject_num個全部表示する
    float interval = 0.08;
    int object_num = 5;
    int now_stock, max_stock = 100;
    
    auto img_ = img;
    DataOf2D p = draw_start_pos;

    for(int i = 0; i < object_num; i++) {
        img_.Draw(p);
        p += {img_.len.x + interval, 0};
    }
    // 座標の用意
    float left = draw_start_pos.x - img_.len.x / 2;
    float lenx_drawing = img_.len.x * object_num + interval * (object_num - 1);
    float right = left + lenx_drawing;
    float begin_hide_x =
        left + float(now_stock) / float(max_stock) * lenx_drawing;
    // 右側から隠す
    draw::RectFilled(begin_hide_x, right, draw_start_pos.y + img_.len.y / 2,
                     draw_start_pos.y - img_.len.y / 2, {0.0, 1.0, 0.0});
}