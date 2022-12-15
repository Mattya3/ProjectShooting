#include <scenes/Title_Scene.hpp>

#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/BattleScene.hpp>
#include <scenes/SelectCards_Scene.hpp>
#include <scenes/ResolverCallbackFunc.hpp>

static void render2() {
    glColor3d(1.0, 1.0, 1.0);
    static const GLfloat diffuse[] = {0.6, 0.1, 0.1, 1.0};
    static const GLfloat specular[] = {0.3, 0.3, 0.3, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);
}
Title_scene::Title_scene(GLFWwindow *window1) {
    register_callback_resolver::init(*this, window1);

    PngTexture go_battle("title/goBattle.png", Location(-0.6, 0.1, 1.2, 0.3));
    PngTexture go_select_card("title/goSelectCard.png",
                              Location(-0.6, -0.4, 1.2, 0.3));

    NextSceneButton *btn_go_battle = new NextSceneButton(-0.6, 0.1, 1.5, 0.5);
    NextSceneButton *b = new NextSceneButton(-0.6, -0.4, 1.2, 0.3);
    b->set_color(0.5, 0.1, 0.8);
    this->add_button(b);
    this->add_button(btn_go_battle);

    while(!glfwWindowShouldClose(window1)) {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_CULL_FACE);
        render2();
        show_component();
        btn_go_battle->button_filled_view();
        go_battle.view();
        go_select_card.view();

        glfwSwapBuffers(window1);
        glfwPollEvents();

        if(b->next_scene) {
            break;
        }
        if(btn_go_battle->next_scene) {
            break;
        }
    }
    if(b->next_scene) {
        SelectCards_Scene csv(window1);
    } else if(btn_go_battle->next_scene) {
        BattleScene bs(window1);
    }
}
void Title_scene::render(GLFWwindow *window1) {}
Title_scene::~Title_scene() {}