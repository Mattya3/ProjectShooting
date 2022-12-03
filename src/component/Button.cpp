#include <component/Button.hpp>

void Button:: action_when_pushed() {
    is_btn_lightup = !is_btn_lightup;
}
bool Button::valid_push_location(double x, double y) {
    return (sx <= x && x <= sx + xlen && sy <= y && y <= sy + ylen);
}
void Button::button_view() {
    if(is_btn_lightup) {
        glBegin(GL_POLYGON);
    } else {
        glBegin(GL_LINE_LOOP);
    }
    glColor3d(0.0, 1.0, 0.0);
    glVertex2d(sx, sy);
    glVertex2d(sx + xlen, sy);
    glVertex2d(sx + xlen, sy + ylen);
    glVertex2d(sx, sy + ylen);
    glEnd();
}
Button::Button(double sx, double sy, double xlen, double ylen)
    : sx(sx), sy(sy), xlen(xlen), ylen(ylen) {}
Button::~Button() {}