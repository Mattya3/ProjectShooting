#include <scenes/Title_Scene.hpp>


#include <component/Image.hpp>
#include <filesystem>
#include <scenes/ChangeStructureView.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <component/NextSceneButton.hpp>
using std::filesystem::current_path;
Title_scene::Title_scene(GLFWwindow *window1) {
    register_callback_resolver::init(*this, window1);

    PngTexture pt(
        (current_path() / filesystem::path("img/ic_launcher.png")).c_str(), 1);
    PngTexture meImg(
        (current_path() / filesystem::path("img/battle/me.png")).c_str(), 2);

    NextSceneButton *b = new NextSceneButton(-0.2, -0.2, 0.4, 0.4);
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
        show_component();
        glDisable(GL_TEXTURE_2D);

        glfwSwapBuffers(window1);
        glfwPollEvents();
        if(b->next_scene) {
            break;
        }
    }
    ChangeStructureView csv(window1);
}
void Title_scene::render(GLFWwindow *window1) {}
Title_scene::~Title_scene() {}