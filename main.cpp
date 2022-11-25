#define GL_SILENCE_DEPRECATION 1
// #include <funcA.hpp>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
using namespace std;
using pdd = pair<double, double>;
using square = pair<pdd, pdd>;
constexpr int WINDOW_width = 640, WINDOW_height = 480;
inline void to_canonical_xy(double &x, double &y) {
    x /= WINDOW_width / 2;
    y /= WINDOW_height / 2;
    y = 1 - y;
    x = x - 1;
}
// square example = {{sx,sy}, {gx, gy}}; 左下、右上
enum class scene {
    title,
    select_card,
    battle,
};
scene scene_id = scene::title;

class Button {
  private:
    double sx, sy, xlen, ylen;
    double r, g, b;
    function<void(void)> func;
    bool is_btn_lightup = false;

  public:
    void set_action(function<void(void)> f) { func = f; }
    void action_when_pushed() {
        func();
        is_btn_lightup = !is_btn_lightup;
    }
    inline bool valid_push_location(double x, double y) {
        return (sx <= x && x <= sx + xlen && sy <= y && y <= sy + ylen);
    }
    void button_view() {
        if(is_btn_lightup) {
            glBegin(GL_POLYGON);
        } else {
            glBegin(GL_LINE_LOOP);
        }
        glColor3d(1.0, 0.0, 0.0);
        glVertex2d(sx, sy);
        glVertex2d(sx + xlen, sy);
        glVertex2d(sx + xlen, sy + ylen);
        glVertex2d(sx, sy + ylen);
        glEnd();
    }
    Button(double sx, double sy, double xlen, double ylen);
    ~Button();
};

Button::Button(double sx, double sy, double xlen, double ylen)
    : sx(sx), sy(sy), xlen(xlen), ylen(ylen) {}

Button::~Button() {}

class Scene {
  private:
  protected:
    vector<Button> btns;

  public:
    virtual void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                                       int mods) {}
    virtual void add_button() {}
};
class Title_scene : public Scene {
  private:
  public:
    void mouse_button_callback(GLFWwindow *pwin, int button, int action,
                               int mods) {
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
    void add_button(Button btn) { btns.push_back(btn); }
    void show_component() {
        for(auto &&e : btns) {
            e.button_view();
        }
    }
    Title_scene();
    ~Title_scene();
};

Title_scene::Title_scene() {}

Title_scene::~Title_scene() {}
void mouse_button_callback(GLFWwindow *pwin, int button, int action, int mods) {

    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        scene_id = scene::battle;
    }
    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        scene_id = scene::title;
    }
}

// GLFWにおいてコールバック関数としてインスタンスメソッドを登録できない
// 間に静的関数をかませることで解決できる。
// add_scene_instanceの後に
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

void draw_grid(square rect, int nx, int ny, double x_interval,
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

int main() {

    GLFWwindow *window1, *window2;

    // ライブラリglfw の初期化
    if(!glfwInit())
        return -1;

    // ウィンドウを作成
    window1 = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    // window2 = glfwCreateWindow(400, 400, "window 2", NULL, NULL);
    if(!window1) {
        glfwTerminate();
        return -1;
    }
    // glfwSetMouseButtonCallback(window1, mouse_button_callback);
    square cards = square(pdd(-1, -0.5), pdd(1.0, 1.0));
    // 作成したウィンドウを，OpenGLの描画関数のターゲットにする
    glfwMakeContextCurrent(window1);

    Button b(-0.5, -0.5, 0.3, 0.3);
    b.set_action([&]() { draw_grid(cards, 3, 3, 0.1, 0.1); });
    Title_scene ts;
    ts.add_button(b);

    register_callback_resolver::init(ts, window1);
    // 描画のループ
    while(!glfwWindowShouldClose(window1)) {
        // 画面を塗りつぶす
        glClear(GL_COLOR_BUFFER_BIT);
        switch(scene_id) {
        case scene::title:
            draw_grid(cards, 4, 2, 0.05, 0.1);
            ts.show_component();
            break;
        case scene::battle:
            draw_grid(cards, 4, 6, 0.05, 0.05);
            break;
        case scene::select_card:
            draw_grid(cards, 4, 2, 0.05, 0.1);
            break;
        default:
            break;
        }

        // 上記描画した図形を表画面のバッファにスワップする
        glfwSwapBuffers(window1);

        // 受け取ったイベント（キーボードやマウス入力）を処理する
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}