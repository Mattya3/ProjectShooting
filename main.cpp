#include <scenes/all_scene.hpp>

using namespace std;
sceneNumber scene_id = sceneNumber::title;

// GLFWにおいてコールバック関数としてインスタンスメソッドを登録できない
// 間に静的関数をかませることで解決できる。
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



int main() {
    GLFWwindow *window1, *window2;
    if(!glfwInit())
        return -1;

    // ウィンドウ作成
    window1 = glfwCreateWindow(WINDOW_width, WINDOW_height, "Hello World", NULL,
                               NULL);
    // window2 = glfwCreateWindow(400, 400, "window 2", NULL, NULL);

    if(!window1) {
        glfwTerminate();
        return -1;
    }
    // 作成したウィンドウを，OpenGLの描画関数のターゲットにする
    glfwMakeContextCurrent(window1);

    Button *b = new Button(-0.5, -0.5, 0.3, 0.3);
    Button *b2 = new Button(0.2, 0.2, 0.2, 0.2);
    class btnap : public Button {
        using Button::Button;

      private:
        bool btn_enable = true;

      public:
        void action_when_pushed() {
            if(btn_enable) {
                auto func = [&](std::promise<double> p, double x) {
                    try {
                        p.set_value(x);
                        this_thread::sleep_for(chrono::milliseconds(2000));

                        scene_id = sceneNumber::title;

                    } catch(...) { p.set_exception(std::current_exception()); }
                };
                promise<double> p;
                future<double> f = p.get_future();

                double x = 3.14159;
                thread th(func, std::move(p), x);
                /* 自スレッドでの処理 */;
                is_btn_lightup = !is_btn_lightup;
                btn_enable = false;
                button_view();

                try {
                    double result = f.get();
                } catch(...) {}
                th.join();

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

    Title_scene ts;
    ts.add_button(b);
    register_callback_resolver::init(ts, window1);

    // 描画のループ
    ChangeStructureView csv;
    scene_id = sceneNumber::select_card;
    register_callback_resolver::init(csv, window1);
    csv.add_button(b);
    csv.add_button(b2);
    csv.add_button(bb);

    while(!glfwWindowShouldClose(window1)) {
        // 初期化
        glClear(GL_COLOR_BUFFER_BIT);

        switch(scene_id) {
        case sceneNumber::title:
            ts.show_component();
            break;
        case sceneNumber::battle:
            glColor3d(0.0, 0.0, 1.0);
            break;
        case sceneNumber::select_card:
            csv.show_component();
            break;
        default:
            break;
        }

        glfwSwapBuffers(window1);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}