#include <Setting.hpp>
#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
// #include <internal/card/Card.hpp>
// #include <internal/card/StructureData.hpp>
#include <internal/card/ChangeStructure.hpp>


#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/SelectCardSub.hpp>
#include <scenes/SelectCards_Scene.hpp>

SelectCardSub::SelectCardSub(int struct_id, GLFWwindow *window) {

    NextSceneButton *bt = new NextSceneButton(-0.9, -0.9, 0.5, 0.5);
    bt->set_color(0.0, 1.0, 0.0);
    add_button(bt);
    GLFWwindow *sub_window =
        glfwCreateWindow(Setting::WINDOW_width, Setting::WINDOW_height,
                         "Card Select", NULL, NULL);
    glfwMakeContextCurrent(sub_window);

    PngTexture back_arrow("test_img/back.png",
                          Location(-0.9, -0.9, 0.49, 0.49));
    NextSceneButton *ii = new NextSceneButton(0, 0, 0.7, 0.7);
    ii->set_color(1.0, 0.0, 0.0);

    register_callback_resolver::init(*this, sub_window);
    

    while(!glfwWindowShouldClose(sub_window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        show_component();
        back_arrow.view();
        gb.view();

        glfwSwapBuffers(sub_window);
        glfwPollEvents();
        if(bt->next_scene) {
            break;
        }
    }
    if(bt->next_scene) {
        glfwDestroyWindow(sub_window);
    }
}

SelectCardSub::~SelectCardSub() {}
