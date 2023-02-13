#include "Button.hpp"
#include <GLFW/glfw3.h>

namespace sbfw {

void Button::draw() {
    // if(is_pushed()) {
    //     glBegin(GL_POLYGON);
    // } else {
    glBegin(GL_LINE_LOOP);
    // }
    if(is_cursor_touched) {
        glColor3d(0, 1, 0);
        is_cursor_touched = false;
    } else {
        glColor3d(col[0], col[1], col[2]);
    }
    if(is_pushed()) {
        glColor3d(1.0, 1.0, 0);
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
    // if(has_texture) {
    tex.Draw();
    // }
}
} // namespace sbfw
