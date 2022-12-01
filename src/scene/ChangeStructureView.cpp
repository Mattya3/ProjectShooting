#include <scenes/ChangeStructureView.hpp>

ChangeStructureView::ChangeStructureView() {}

ChangeStructureView::~ChangeStructureView() {}
void ChangeStructureView::mouse_button_callback(GLFWwindow *pwin, int button,
                                                int action, int mods) {
    double mousex, mousey;
    glfwGetCursorPos(pwin, &mousex, &mousey);
    to_canonical_xy(mousex, mousey);
    for(auto &&btn : btns) {
        if(btn.valid_push_location(mousex, mousey)) {
            btn.action_when_pushed();
        } else {
            cout << "no valid"
                 << "\n";
            cout << mousex << ',' << mousey << "\n";
        }
    }
}
void ChangeStructureView::add_button(Button btn) { btns.push_back(btn); }
void ChangeStructureView::show_component() {
    for(auto &&e : btns) {
        e.button_view();
    }
}