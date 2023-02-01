#pragma once
#include <bits/stdc++.h>

#include <GLFW/glfw3.h>

#include <DataOf2D.hpp>

#include "../texture/ImgUnit.hpp"
#include <scene/Setting.hpp>
namespace sbfw {
class Button {
  public:
    // 画像無し
    Button(DataOf2D pos, DataOf2D len,
           std::vector<float> col = std::vector<float>(3, 1.0f))
        : has_texture(false), pos(pos), len(len), col(col) {}
    // 画像あり
    Button(texture::ImgUnit te, std::function<void(void)> action)
        : tex(te), pos(te.pos), len(te.len), has_texture(true), action(action),
          up(pos.y + len.y / 2 * tex.scale), low(pos.y - len.y / 2 * tex.scale),
          left(pos.x - len.x / 2 * tex.scale),
          right(pos.x + len.x / 2 * tex.scale) {}

    texture::ImgUnit tex;
    Setting setting{};

  protected:
    bool has_texture = false;

    DataOf2D pos; // 中心座標
    DataOf2D len; // 横幅と縦幅

    // 色 RGB
    std::vector<float> col = std::vector<float>(3, 1.0);
    bool btn_enable = false;

    std::function<void(void)> action;

    float left, right, up, low;

  public:
    inline void set_color(std::vector<float> &color_vec) {
        assert(color_vec.size() == 3);
        col = std::vector<float>(color_vec);
    }

    // ボタンが押された時trueを返す (インスタンス外で解決したい処理がある時)
    // ボタンの種類による挙動の変化は子クラスでoverrideすることで対応
    inline bool is_pushed() { return btn_enable; }

    // ボタンが押されたときの処理
    // すなわちvalid_push_locationだったときにmouse_callbackで使われる
    void action_when_pushed() {
        btn_enable = true;
        action();
    }
    // カーソルが上に来たが押下されていない時
    bool is_cursor_touched = false;
    void action_when_cursor_touched() { is_cursor_touched = true; }
    // 引数(x,y)がボタンの領域にあるときtrue
    inline bool valid_push_location(float x, float y) {
        return (left <= x && x <= right && low <= y && y <= up);
    }

    // ボタンを表示する
    virtual void draw() {
        if(is_pushed()) {
            glBegin(GL_POLYGON);
        } else {
            glBegin(GL_LINE_LOOP);
        }
        if(is_cursor_touched) {
            glColor3d(0, 1, 0);
            is_cursor_touched = false;
        } else {
            glColor3d(col[0], col[1], col[2]);
        }
        float ratio = 1.2;
        glVertex3d(pos.x - len.x / 2 * tex.scale * ratio,
                   pos.y - len.y / 2 * tex.scale * ratio, 0);
        glVertex3d(pos.x + len.x / 2 * tex.scale * ratio,
                   pos.y - len.y / 2 * tex.scale * ratio, 0);
        glVertex3d(pos.x + len.x / 2 * tex.scale * ratio,
                   pos.y + len.y / 2 * tex.scale * ratio, 0);
        glVertex3d(pos.x - len.x / 2 * tex.scale * ratio,
                   pos.y + len.y / 2 * tex.scale * ratio, 0);
        glEnd();
        if(has_texture) {
            tex.view();
        }
    }
};
} // namespace sbfw
