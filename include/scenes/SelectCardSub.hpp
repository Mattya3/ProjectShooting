#include <scenes/Scene.hpp>
class SelectCardSub : Scene {
  private:
    /* data */
    bool *tm;

  public:
    void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                               int mods) override {
        double mousex, mousey;

        glfwGetCursorPos(pwin, &mousex, &mousey);
        Setting::to_canonical_xy(mousex, mousey);
        for(auto &&btn : btns) {
            if(btn->valid_push_location(mousex, mousey)) {
                btn->action_when_pushed();
            } else {
                cout << mousex << ',' << mousey << "\n";
            }
        }
        cout << "btn sz"<<btns.size() << endl;
        cout << "mouse callback called" << endl;
    }
    SelectCardSub(int struct_id, GLFWwindow *window);
    ~SelectCardSub();
};
