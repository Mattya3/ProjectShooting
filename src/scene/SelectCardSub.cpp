#include <Setting.hpp>
#include <component/Button_anyTimes.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/ChangeStructureView.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/SelectCardSub.hpp>
SelectCardSub::SelectCardSub(int struct_id, GLFWwindow *window) {

    NextSceneButton *bt = new NextSceneButton(0, 0, 0.5, 0.5);
    bt->set_color(0.0, 1.0, 0.0);
    add_button(bt);
    GLFWwindow *sub_window =
        glfwCreateWindow(Setting::WINDOW_width, Setting::WINDOW_height,
                         "Card Select", NULL, NULL);
    glfwMakeContextCurrent(sub_window);

    register_callback_resolver::init(*this, sub_window);

    while(!glfwWindowShouldClose(sub_window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        show_component();
        glfwSwapBuffers(sub_window);
        glfwPollEvents();
        glBegin(GL_LINE_LOOP);
        glVertex2d(-0.5, -0.5);
        glVertex2d(1.0, 1.0);
        glVertex2d(0.5, 1.0);
        glVertex2d(0.3, -1.0);
        glEnd();
        if(bt->next_scene) {
            break;
        }
    }
    if(bt->next_scene) {
        glfwDestroyWindow(sub_window);
    }
}

SelectCardSub::~SelectCardSub() {}
