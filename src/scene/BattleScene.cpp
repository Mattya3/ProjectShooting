#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/BattleScene.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/Title_Scene.hpp>

BattleScene::BattleScene(GLFWwindow *window1) {
    register_callback_resolver::init(*this, window1);
    PngTexture me("battle/me.png", Location(-0.8, -0.8, 0.4, 0.4));
    PngTexture go_select_card("test_img/go_title.png",
                              Location(-0.6, -0.4, 1.2, 0.3));
    PngTexture bullet("battle/bulletMe.png", Location(-0.8, -0.8, 0.1, 0.1));

    NextSceneButton *b = new NextSceneButton(-0.6, -0.4, 1.2, 0.3);
    Button_anyTimes *transBtn = new Button_anyTimes(0.3, 0.3, 0.5, 0.5);
    b->set_color(0.5, 0.1, 0.8);
    this->add_button(b);
    transBtn->set_color(0.1, 0.8, 0.2);
    this->add_button(transBtn);
    int dir = 1;

    while(!glfwWindowShouldClose(window1)) {
        glClear(GL_COLOR_BUFFER_BIT);
        show_component();
        go_select_card.view();
        bullet.view();
        // bullet.view_clone(me.loc);
        me.view();
        glfwSwapBuffers(window1);
        glfwPollEvents();
        if(transBtn->is_pushed()) {
            me.loc.sx += 0.07 * dir;
            me.loc.sy += 0.07 * dir;
            if(me.loc.sx >= 1 && me.loc.sy >= 1) {
                dir *= -1;
            }
            bullet.loc.sy += 0.1 * dir;
            if(bullet.loc.sy > 1) {
                bullet.loc.sy = me.loc.sy;
            }
        }
        if(b->next_scene) {
            break;
        }
    }
    if(b->next_scene) {
        Title_scene ts(window1);
    }
}

BattleScene::~BattleScene() {}
