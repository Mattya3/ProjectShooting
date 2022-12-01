// #include <funcA.hpp>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include <scenes/all_scene.hpp>

using namespace std;
using pdd = pair<double, double>;
using square = pair<pdd, pdd>;
const int WINDOW_width = 800, WINDOW_height = 700;

// square example = {{sx,sy}, {gx, gy}}; 左下、右上
enum class scene {
    title,
    select_card,
    battle,
};
scene scene_id = scene::title;


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
    
    Title_scene ts;
    ts.add_button(b);
    register_callback_resolver::init(ts, window1);
    // 描画のループ
    ChangeStructureView csv;

    while(!glfwWindowShouldClose(window1)) {
        // 画面を塗りつぶす
        glClear(GL_COLOR_BUFFER_BIT);

        switch(scene_id) {
        case scene::title:
            draw_grid(cards, 4, 2, 0.05, 0.1);
            ts.show_component();
            break;
        case scene::battle:
            glColor3d(0.0,0.0,1.0);
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