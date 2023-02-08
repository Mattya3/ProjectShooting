#include <bits/stdc++.h>

using namespace std;
#include "SBFW/sbfw.hpp"

int main() {
    GLFWwindow *window;
    if(!glfwInit())
        return -1;

    window = glfwCreateWindow(800, 700, "Hello World", NULL, NULL);
    assert(window);
    if(!window) {
        glfwTerminate();
        return -1;
    }
    // 作成したウィンドウを，OpenGLの描画関数のターゲットに
    glfwMakeContextCurrent(window);

    sbfw::ElemInfo elgo_select({0, -0.5}, "title/goSelectCard.png", 0.3);

    sbfw::ElemInfo elboss({0, 0.5}, "status/redstar.png", 3);
    sbfw::ElemInfo elfighter({0.2, 0.2}, "battle/me.png", 5);
    sbfw::ElemInfo elback_arrow({-0.7, -0.7}, "test_img/back.png", 0.2);
    sbfw::ElemInfo elOK({0.8, -0.8}, "select_card_sub/OK.png", 0.3);
    sbfw::ElemInfo elleft_arrow({-0.2, -0.8}, "select_card_sub/leftarrow.png",
                                0.4);
    sbfw::ElemInfo elright_arrow({0.2, -0.8}, "select_card_sub/rightarrow.png",
                                 0.4);
    auto [title, select, score] =
        sbfw::scene::prepare_scenes<3>(); // 構造化束縛で1つずつ
    cout << "Hello" << endl;
    title->add_image(elboss);
    cout << "Hello" << endl;
    title->set_window_name("title");
    cout << "Hello" << endl;
    select->set_window_name("select");
    cout << "Hello" << endl;
    title->def_transtion_to(elgo_select, select);
    cout << "Hello" << endl;

    title->start(window);
    return 0;
}