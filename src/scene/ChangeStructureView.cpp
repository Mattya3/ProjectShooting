#include <scenes/ChangeStructureView.hpp>
#include <scenes/Title_Scene.hpp>
float g_angle = 0.0;
// GLFWにおいてコールバック関数としてインスタンスメソッドを登録できない
// 間に静的関数をかませることで解決する。
// シーンの各種マウスキー入力監視関数をコールバック登録する
static Scene *sc_ptr;
class register_callback_resolver {
  private:
    static void mouse_func(GLFWwindow *pwin, int button, int action, int mods) {
        sc_ptr->mouse_button_callback(pwin, button, action, mods);
    }

  public:
    static void init(Scene &sc, GLFWwindow *pwin) {
        sc_ptr = &sc;
        glfwSetMouseButtonCallback(pwin, mouse_func);
    }
};

void f() {
    static const GLfloat vtx3[] = {
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    };

    glVertexPointer(2, GL_FLOAT, 0, vtx3);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_MULTISAMPLE);
    glMatrixMode(GL_MODELVIEW);
    glEnableClientState(GL_VERTEX_ARRAY);

    // 回転アニメーション
    glPushMatrix();
    // glTranslatef(320.0f, 240.0f, 0.0f);
    glRotatef(g_angle, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_QUADS, 0, 4);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
}
ChangeStructureView::ChangeStructureView(GLFWwindow *window1) {
    register_callback_resolver::init(*this, window1);
    Button *b = new Button(-0.5, -0.5, 0.3, 0.3);
    Button *b2 = new Button(0.2, 0.2, 0.2, 0.2);
    add_button(b);
    add_button(b2);
    class btnap : public Button {
        using Button::Button;

      private:
        bool btn_enable = true;

      public:
        bool next_scene = false;
        void action_when_pushed() {
            if(btn_enable) {
                is_btn_lightup = !is_btn_lightup;
                next_scene = true;
                btn_enable = false;
                button_view();
            } else {
                cout << "now false" << endl;
            }
        }
        void button_view() {
            if(is_btn_lightup) {
                glBegin(GL_POLYGON);
            } else {
                glBegin(GL_LINE_LOOP);
            }
            glColor3d(0.0, 1.0, 1.0);
            glVertex2d(sx, sy);
            glVertex2d(sx + xlen, sy);
            glVertex2d(sx + xlen, sy + ylen);
            glVertex2d(sx, sy + ylen);
            glEnd();
        }
    };
    btnap *bb = new btnap(-0.5, 0.2, 0.3, 0.3);
    add_button(bb);

    render(window1);
    while(!glfwWindowShouldClose(window1)) {
        // 初期化
        glClear(GL_COLOR_BUFFER_BIT);

        show_component();
        g_angle += 0.05;
        f();

        glfwSwapBuffers(window1);
        glfwPollEvents();

        if(bb->next_scene) {
            break;
        }
    }
    Title_scene ts(window1);
}

void ChangeStructureView::render(GLFWwindow *window1) {}
void ChangeStructureView::mouse_button_callback(GLFWwindow *pwin, int button,
                                                int action, int mods) {
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
}
void ChangeStructureView::add_button(Button *btn) { btns.push_back(btn); }
void ChangeStructureView::show_component() {
    auto show = [](double sx, double sy, double xlen, double ylen,
                   string color) {
        sx /= Setting::WINDOW_width / 2;
        sy /= Setting::WINDOW_height / 2;
        sx -= 1;
        sy -= 1;
        xlen /= Setting::WINDOW_width / 2;
        ylen /= Setting::WINDOW_height / 2;
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

ChangeStructureView::~ChangeStructureView() {}