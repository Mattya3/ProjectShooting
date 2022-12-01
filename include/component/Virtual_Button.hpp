#pragma once
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
using namespace std;

class Virtual_Button {
  private:
    double sx, sy, xlen, ylen;
    double r, g, b;
    bool is_btn_lightup = false;

  public:
    virtual void action_when_pushed() {}
    inline bool valid_push_location(double x, double y) {
        return (sx <= x && x <= sx + xlen && sy <= y && y <= sy + ylen);
    }
    void button_view() {
        if(is_btn_lightup) {
            glBegin(GL_POLYGON);
        } else {
            glBegin(GL_LINE_LOOP);
        }
        glColor3d(1.0, 0.0, 0.0);
        glVertex2d(sx, sy);
        glVertex2d(sx + xlen, sy);
        glVertex2d(sx + xlen, sy + ylen);
        glVertex2d(sx, sy + ylen);
        glEnd();
    }
    Virtual_Button(double sx, double sy, double xlen, double ylen);
    ~Virtual_Button();
};
