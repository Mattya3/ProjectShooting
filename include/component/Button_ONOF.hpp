#pragma once
#include <component/ButtonBase.hpp>
#include <DataOf2D.hpp>
using namespace std;

class Button_ONOF : public ButtonBase {
    using ButtonBase::ButtonBase;

  public:
     void action_when_pushed() override;
     void button_view() override {
        glBegin(GL_LINE_LOOP);
        glColor3d(r, g, b);
        glVertex2d(sx, sy);
        glVertex2d(sx + xlen, sy);
        glVertex2d(sx + xlen, sy + ylen);
        glVertex2d(sx, sy + ylen);
        glEnd();
        if(has_texture) {
            btn_view.view();
        }
    }
};
