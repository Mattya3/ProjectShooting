#pragma once
#include <component/Button.hpp>

class NextSceneButton : public Button {
    using Button::Button;

  private:
    bool btn_enable = true;

  public:
    bool next_scene = false;
    void action_when_pushed() {
        if(btn_enable) {
            is_btn_lightup = !is_btn_lightup;
            next_scene = true;
            btn_enable = false;
            button_view();
        } else {
            cout << "now false" << endl;
        }
    }
    void button_view() {
        if(is_btn_lightup) {
            glBegin(GL_POLYGON);
        } else {
            glBegin(GL_LINE_LOOP);
        }
        glColor3d(0.0, 1.0, 1.0);
        glVertex2d(sx, sy);
        glVertex2d(sx + xlen, sy);
        glVertex2d(sx + xlen, sy + ylen);
        glVertex2d(sx, sy + ylen);
        glEnd();
    }
};