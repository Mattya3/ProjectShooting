#include <Setting.hpp>
#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/ChangeStructureView.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/SelectCardSub.hpp>
using pdd = pair<double, double>;
using square = pair<pdd, pdd>;
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

void show_png(double sx, double sy, double xlen, double ylen) {
    glColor3d(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, 3);
    glEnable(GL_TEXTURE_2D);
    glNormal3d(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2d(0.0, 1.0);
    glVertex3d(sx, sy, 0.0);
    glTexCoord2d(1.0, 1.0);
    glVertex3d(sx + xlen, sy, 0.0);
    glTexCoord2d(1.0, 0.0);
    glVertex3d(sx + xlen, sy + ylen, 0.0);
    glTexCoord2d(0.0, 0.0);
    glVertex3d(sx, sy + ylen, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
SelectCardSub::SelectCardSub(int struct_id, GLFWwindow *window) {

    NextSceneButton *bt = new NextSceneButton(-0.9, -0.9, 0.5, 0.5);
    bt->set_color(0.0, 1.0, 0.0);
    add_button(bt);
    GLFWwindow *sub_window =
        glfwCreateWindow(Setting::WINDOW_width, Setting::WINDOW_height,
                         "Card Select", NULL, NULL);
    glfwMakeContextCurrent(sub_window);

    PngTexture back_arrow("back.png", 3);
    NextSceneButton *ii = new NextSceneButton(0, 0, 0.7, 0.7);
    ii->set_color(1.0, 0.0, 0.0);
    register_callback_resolver::init(*this, sub_window);
    square sq = {{-0.8, -0.4}, {0.8, 1}};
    while(!glfwWindowShouldClose(sub_window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        show_component();
        show_png(-0.9, -0.9, 0.49, 0.49);
        draw_grid(sq, 3, 4, 0.05, 0.05);

        glfwSwapBuffers(sub_window);
        glfwPollEvents();
        if(bt->next_scene) {
            break;
        }
    }
    if(bt->next_scene) {
        glfwDestroyWindow(sub_window);
    }
}

SelectCardSub::~SelectCardSub() {}
