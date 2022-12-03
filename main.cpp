#include <bits/stdc++.h>
#include <component/Image.hpp>
#include <filesystem>
#include <scenes/all_scene.hpp>

using namespace std;
using std::filesystem::current_path;
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
    Setting::scene_id=sceneNumber::title;
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
                scene_id = sceneNumber::title;
                is_btn_lightup = !is_btn_lightup;
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

    Title_scene ts;
    ts.add_button(b);
    register_callback_resolver::init(ts, window1);

    ChangeStructureView csv;
    scene_id = sceneNumber::select_card;
    register_callback_resolver::init(csv, window1);
    csv.add_button(b);
    csv.add_button(b2);
    csv.add_button(bb);

    // glGenTextures(1, &g_texID);
    // setupTexture( g_texID, "img/out1.ppm", 256, 256);
    PngTexture pt(
        (current_path() / filesystem::path("img/ic_launcher.png")).c_str(), 1);
    while(!glfwWindowShouldClose(window1)) {
        // 初期化
        glClear(GL_COLOR_BUFFER_BIT);

        switch(scene_id) {
        case sceneNumber::title:
            // ts.show_component();
            /* テクスチャマッピング開始 */
            glEnable(GL_TEXTURE_2D);

            /* １枚の４角形を描く */
            glNormal3d(0.0, 0.0, 1.0);
            glBegin(GL_QUADS);
            glTexCoord2d(0.0, 1.0);
            glVertex3d(-1.0, -1.0, 0.0);
            glTexCoord2d(1.0, 1.0);
            glVertex3d(1.0, -1.0, 0.0);
            glTexCoord2d(1.0, 0.0);
            glVertex3d(1.0, 1.0, 0.0);
            glTexCoord2d(0.0, 0.0);
            glVertex3d(-1.0, 1.0, 0.0);
            glEnd();
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