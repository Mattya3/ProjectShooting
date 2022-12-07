#include <scenes/ChangeStructureView.hpp>

#include <component/Button_anyTimes.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
#include <scenes/SelectCardSub.hpp>
#include <scenes/Title_Scene.hpp>
static float g_angle = 0.0;
// GLFWにおいてコールバック関数としてインスタンスメソッドを登録できない
// 間に静的関数をかませることで解決する。
// シーンの各種マウスキー入力監視関数をコールバック登録する

void f() {
    static const GLfloat vtx3[] = {
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    };

    glVertexPointer(2, GL_FLOAT, 0, vtx3);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_MULTISAMPLE);
    glMatrixMode(GL_MODELVIEW);
    glEnableClientState(GL_VERTEX_ARRAY);

    // 回転アニメーション
    glPushMatrix();
    // glTranslatef(320.0f, 240.0f, 0.0f);
    glRotatef(g_angle, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_QUADS, 0, 4);
    glPopMatrix();

    glDisableClientState(GL_VERTEX_ARRAY);
}

ChangeStructureView::ChangeStructureView(GLFWwindow *window1) {

    register_callback_resolver::init(*this, window1);

    Button_anyTimes *b = new Button_anyTimes(-0.5, -0.5, 0.3, 0.3);
    Button_anyTimes *b2 = new Button_anyTimes(0.2, 0.2, 0.2, 0.2);
    add_button(b);
    add_button(b2);

    NextSceneButton *bb = new NextSceneButton(-0.5, 0.2, 0.3, 0.3);
    bb->set_color(0.0, 0.0, 0.0);
    add_button(bb);

    vector<Button_anyTimes *> card_struct(3);
    double x_interval = 0.1, y_pos = -0.7, x_pos = -1 + x_interval;
    double xlen = (2.0 - x_interval * 4) / 3, ylen = 1.2;
    for(int i = 0; i < 3; i++) {
        card_struct[i] = new Button_anyTimes(x_pos, y_pos, xlen, ylen);
        x_pos += xlen + x_interval;
        card_struct[i]->set_color(0.0, 0.8, 0.3);
        this->add_button(card_struct[i]);
    }

    int card_struct_id = 0;
    bool is_in_sub_window = false;
    while(!glfwWindowShouldClose(window1)) {

        render();
        glfwSwapBuffers(window1);
        glfwPollEvents();

        if(bb->next_scene) {
            break;
        }
        for(int id = 0; id < 3; id++) {
            if(card_struct[id]->is_pushed()) {
                cout << id << endl;
                card_struct_id = id;
                SelectCardSub scs(card_struct_id, window1);

                register_callback_resolver::init(*this, window1);
                glfwMakeContextCurrent(window1);
            }
        }
    }
    if(bb->next_scene) {
        Title_scene ts(window1);
    }
}

void ChangeStructureView::render() {
    // 初期化
    glClear(GL_COLOR_BUFFER_BIT);

    show_component();
    g_angle += 0.05;
    f();
}

void ChangeStructureView::show_component() {
    for(auto &&e : btns) {
        e->button_view();
    }
}

ChangeStructureView::~ChangeStructureView() {}