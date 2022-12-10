#pragma once
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
using namespace std;

class ButtonBase {
  protected:
    double sx, sy, xlen, ylen;
    double r = 1.0, g = 1.0, b = 1.0;
    bool btn_enable = false;

  public:
    virtual inline void set_color(double r, double g, double b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }
    virtual inline void set_color(vector<double> &color_vec) {
        assert(color_vec.size() == 3);
        this->r = color_vec[0];
        this->g = color_vec[1];
        this->b = color_vec[2];
    }

    // ボタンが押された時trueを返す (インスタンス外で解決したい処理がある時)
    // ボタンの種類による挙動の変化は子クラスでoverrideすることで対応
    virtual inline bool is_pushed() { return btn_enable; }

    // ボタンが押されたときの処理
    // すなわちvalid_push_locationだったときにmouse_callbackで使われる
    virtual void action_when_pushed() {
        cout << "need override" << endl;
        btn_enable = true;
        // exit(1);
    }

    // 引数(x,y)がボタンの領域にあるときtrue
    virtual bool valid_push_location(double x, double y) {
        return (sx <= x && x <= sx + xlen && sy <= y && y <= sy + ylen);
    }

    // ボタンを表示する
    virtual void button_view() {
        if(is_pushed()) {
            glBegin(GL_POLYGON);
        } else {
            glBegin(GL_LINE_LOOP);
        }
        glColor3d(r, g, b);
        glVertex2d(sx, sy);
        glVertex2d(sx + xlen, sy);
        glVertex2d(sx + xlen, sy + ylen);
        glVertex2d(sx, sy + ylen);
        glEnd();
    }
    void button_filled_view() {
        glBegin(GL_POLYGON);
        glColor3d(r, g, b);
        glVertex2d(sx, sy);
        glVertex2d(sx + xlen, sy);
        glVertex2d(sx + xlen, sy + ylen);
        glVertex2d(sx, sy + ylen);
        glEnd();
    }
    // (sx, sy)は左下を表す。xlen,ylenでボタンの幅と高さを指定する。
    // -1<= sx,sy <= 1
    // 0<=xlen,ylen<=2
    ButtonBase(double sx, double sy, double xlen, double ylen)
        : sx(sx), sy(sy), xlen(xlen), ylen(ylen) {}
    ~ButtonBase() {}
};
