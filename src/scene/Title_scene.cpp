#include <component/Image.hpp>
#include <filesystem>
#include <scenes/Title_Scene.hpp>
using std::filesystem::current_path;
Title_scene::Title_scene(GLFWwindow *window1) {
    PngTexture pt(
        (current_path() / filesystem::path("img/ic_launcher.png")).c_str(), 1);

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
    btnap *b = new btnap(-0.2, -0.2, 0.4, 0.4);
    add_button(b);

    while(!glfwWindowShouldClose(window1)) {
        // 初期化
        glClear(GL_COLOR_BUFFER_BIT);

        show_component();
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

        glfwSwapBuffers(window1);
        glfwPollEvents();
    }
}
void Title_scene::render(GLFWwindow *window1) {}
Title_scene::~Title_scene() {}