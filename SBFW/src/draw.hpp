#pragma once
#include "math2D/DataOf2D.hpp"

#include <GLFW/glfw3.h>
#include <bits/stdc++.h>

namespace draw {
inline void RectLine(DataOf2D pos, DataOf2D len,
                     std::array<double, 3> col = {0.0, 0.0, 0.0}) {
    glBegin(GL_LINE_LOOP);
    glColor3d(col[0], col[1], col[2]);
    glVertex2d(pos.x - len.x / 2, pos.y - len.y / 2);
    glVertex2d(pos.x + len.x / 2, pos.y - len.y / 2);
    glVertex2d(pos.x + len.x / 2, pos.y + len.y / 2);
    glVertex2d(pos.x - len.x / 2, pos.y + len.y / 2);
    glEnd();
}
inline void RectFilled(DataOf2D pos, DataOf2D len,
                       std::array<double, 3> col = {0.0, 0.0, 0.0}) {
    glBegin(GL_POLYGON);
    glColor3d(col[0], col[1], col[2]);
    glVertex2d(pos.x - len.x / 2, pos.y - len.y / 2);
    glVertex2d(pos.x + len.x / 2, pos.y - len.y / 2);
    glVertex2d(pos.x + len.x / 2, pos.y + len.y / 2);
    glVertex2d(pos.x - len.x / 2, pos.y + len.y / 2);
    glEnd();
}
inline void RectFilled(float left, float right, float up, float down,
                       std::array<double, 3> col = {0.0, 0.0, 0.0}) {
    glBegin(GL_POLYGON);
    glColor3d(col[0], col[1], col[2]);
    glVertex2d(left, down);
    glVertex2d(right, down);
    glVertex2d(right, up);
    glVertex2d(left, up);
    glEnd();
}
inline void Line(DataOf2D start, DataOf2D end, float width_scale) {
    float width;
    glGetFloatv(GL_LINE_WIDTH, &width);

    glLineWidth(width * width_scale);

    glBegin(GL_LINES);
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
    glEnd();

    glLineWidth(width);
}
inline void DrawPoint(float x, float y, char c) {
    glBegin(GL_POLYGON);
    if(c == 'R') {
        glColor3d(1.0, 0.0, 0.0);
    } else if(c == 'G') {
        glColor3d(0.0, 1.0, 0.0);
    } else if(c == 'B') {
        glColor3d(0.0, 0.0, 1.0);
    }

    glVertex2d(x, y);
    glVertex2d(x + 0.01, y);
    glVertex2d(x + 0.01, y + 0.01);
    glVertex2d(x, y + 0.01);
    glEnd();

} // namespace graphic

} // namespace draw
