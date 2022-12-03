#include <scenes/ChangeStructureView.hpp>
ChangeStructureView::ChangeStructureView() {}
const int WINDOW_width=800, WINDOW_height=700;

ChangeStructureView::~ChangeStructureView() {}
void ChangeStructureView::mouse_button_callback(GLFWwindow *pwin, int button,
                                                int action, int mods) {
    double mousex, mousey;
    glfwGetCursorPos(pwin, &mousex, &mousey);
    to_canonical_xy(mousex, mousey);
for(auto &&btn : btns) {
        if(btn->valid_push_location(mousex, mousey)) {
            btn->action_when_pushed();
        } else {
            cout << mousex << ',' << mousey << "\n";
        }
    }
}
void ChangeStructureView::add_button(Button *btn) { btns.push_back(btn); }
void ChangeStructureView::show_component() {
    auto show = [](double sx, double sy, double xlen, double ylen,
                   string color) {
        sx /= WINDOW_width / 2;
        sy /= WINDOW_height / 2;
        sx -= 1;
        sy -= 1;
        xlen /= WINDOW_width / 2;
        ylen /= WINDOW_height / 2;
        glBegin(GL_POLYGON);
        if(color == "red") {
            glColor3d(1.0, 0.0, 0.0);
        } else if(color == "blue") {
            glColor3d(0.0, 0.0, 1.0);
        } else if(color == "green") {
            glColor3d(0.0, 1.0, 0.0);
        }

        glVertex2d(sx, sy);
        glVertex2d(sx + xlen, sy);
        glVertex2d(sx + xlen, sy + ylen);
        glVertex2d(sx, sy + ylen);
        glEnd();
    };
    show(50, 200, 200, 300, "red");
    show(60, 340, 180, 100, "green");

    show(300, 200, 200, 300, "red");
    show(310, 340, 180, 100, "green");

    show(550, 200, 200, 300, "red");
    show(560, 340, 180, 100, "green");
    for(auto &&e : btns) {
        e->button_view();
    }
}