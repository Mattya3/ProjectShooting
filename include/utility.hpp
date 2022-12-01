#pragma once
extern const int WINDOW_width, WINDOW_height;
using pdd = pair<double, double>;
using square = pair<pdd, pdd>;
inline void to_canonical_xy(double &x, double &y) {
    x /= WINDOW_width / 2;
    y /= WINDOW_height / 2;
    y = 1 - y;
    x = x - 1;
}

inline void draw_grid(square rect, int nx, int ny, double x_interval,
               double y_interval) {
    double sx = rect.first.first + x_interval,
           sy = rect.first.second + y_interval;
    double xlen =
        ((rect.second.first - rect.first.first) - (nx + 1) * x_interval) / nx;
    double ylen =
        ((rect.second.second - rect.first.second) - (ny + 1) * y_interval) / ny;
    for(int i = 0; i < ny; i++) {
        for(int j = 0; j < nx; j++) {

            glBegin(GL_LINE_LOOP);
            glVertex2d(sx, sy);
            glVertex2d(sx + xlen, sy);
            glVertex2d(sx + xlen, sy + ylen);
            glVertex2d(sx, sy + ylen);
            glEnd();
            sx += xlen + x_interval;
        }
        sx = rect.first.first + x_interval;
        sy += ylen + y_interval;
    }
}

