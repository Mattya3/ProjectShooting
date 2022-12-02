#pragma once
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
using namespace std;

class Button {
  private:
    double sx, sy, xlen, ylen;
    double r, g, b;
    bool is_btn_lightup = false;

  public:
    inline void action_when_pushed() {
        is_btn_lightup = !is_btn_lightup;
        cout << "hello" << "\n";
    }
    inline bool valid_push_location(double x, double y) {
        return (sx <= x && x <= sx + xlen && sy <= y && y <= sy + ylen);
    }
    inline void button_view() {
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
    Button(double sx, double sy, double xlen, double ylen){}
    ~Button(){}
};
