#pragma once
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
using namespace std;

class Button {
  protected:
    double sx, sy, xlen, ylen;
    double r, g, b;
    bool is_btn_lightup = false;
    bool btn_enable = true;

  public:
    virtual void action_when_pushed();
    virtual bool valid_push_location(double x, double y);
    virtual void button_view();
    Button(double sx, double sy, double xlen, double ylen);
    ~Button();
};
