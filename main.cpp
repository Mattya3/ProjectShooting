#include <scenes/Title_Scene.hpp>
#include <setting.hpp>
using namespace std;
#include "SBFW/sbfw.hpp"
#include "filename.hpp"

int main() {
    GLFWwindow *window;
    if(!glfwInit())
        return -1;

    window = glfwCreateWindow(sbfw::setting.WINDOW_width,
                              sbfw::setting.WINDOW_height, "Hello World", NULL,
                              NULL);
    assert(window);

    if(!window) {
        glfwTerminate();
        return -1;
    }
    // 作成したウィンドウを，OpenGLの描画関数のターゲットに
    glfwMakeContextCurrent(window);

    sbfw::ElemInfo elgo_battle({0, 0.5}, "title/goBattle.png", 0.3);
    sbfw::ElemInfo elgo_select({0, -0.5}, "title/goSelectCard.png", 0.3);
    sbfw::ElemInfo elgo_back({-0.5, -0.5}, "test_img/go_title.png");
    sbfw::ElemInfo eldroid({-0.5, 0.3}, "ic_launcher.png");
    sbfw::ElemInfo eldroid2({+0.5, 0.3}, "ic_launcher.png");
    sbfw::ElemInfo elboss({0, 0.5}, "status/redstar.png", 3);
    sbfw::ElemInfo elfighter({0.2, 0.2}, "battle/me.png", 5);
    sbfw::ElemInfo elback_arrow({-0.7, -0.7}, "test_img/back.png", 0.2);
    sbfw::ElemInfo elOK({0.8, -0.8}, "select_card_sub/OK.png", 0.3);
    sbfw::ElemInfo elleft_arrow({-0.2, -0.8}, "select_card_sub/leftarrow.png",
                                0.4);
    sbfw::ElemInfo elright_arrow({0.2, -0.8}, "select_card_sub/rightarrow.png",
                                 0.4);

    vector<sbfw::ElemInfo> elcards(card_fnames.size());
    int card_num = elcards.size();
    int columns = 4, sub_scene_num = 3, each_scene_num = 12;
    printf("%d, %d\n", each_scene_num, card_fnames.size());
    float sx = -0.7, sy = 0.7; // 31 = 12 + 12 + 7;
    for(int i = 0; i < card_num; i++) {
        int one_scene_idx = i % each_scene_num;
        DataOf2D d = {sx + one_scene_idx % columns * 0.4f,
                      sy - one_scene_idx / columns * 0.4f};
        elcards[i] = sbfw::ElemInfo(d, "card/" + card_fnames[i], 0.6);
        // d.dump();
    }

    auto [title, select, game, score] = sbfw::scene::prepare_scenes<4>();
    auto [sub1, sub2, sub3] = sbfw::scene::prepare_scenes<3>();

    title->set_window_name("Title");
    select->set_window_name("select");
    sub1->set_window_name("sub1");
    sub2->set_window_name("sub2");
    sub3->set_window_name("sub3");

    game->set_window_name("game");
    score->set_window_name("score");

    title->add_button(elback_arrow, []() { cout << "hello" << endl; });

    int select_key;
    class functor {
      private:
        int idx;

      public:
        functor(int idx) : idx(idx) {}
        void operator()() { cout << "You Select " << idx << endl; }
    };
    for(int i = 0; i < card_num; i++) {
        switch(i / each_scene_num) {
        case 0:
            sub1->add_button(elcards[i], functor(i));
            break;
        case 1:
            sub2->add_button(elcards[i], functor(i));
            break;
        case 2:
            sub3->add_button(elcards[i], functor(i));
            break;
        default:
            break;
        }
    }

    title->def_transtion_to(elgo_select, select);
    title->def_transtion_to(elgo_battle, game);
    select->def_transtion_to(elback_arrow, title);
    select->def_transtion_to(elfighter, sub1);

    sub1->def_transtion_to(elback_arrow, select);
    sub1->def_transtion_to(elOK, select);
    sub1->def_transtion_to(elright_arrow, sub2);
    sub2->def_transtion_to(elback_arrow, select);
    sub2->def_transtion_to(elOK, select);
    sub2->def_transtion_to(elright_arrow, sub3);
    sub2->def_transtion_to(elleft_arrow, sub1);
    sub3->def_transtion_to(elback_arrow, select);
    sub3->def_transtion_to(elOK, select);
    sub3->def_transtion_to(elleft_arrow, sub2);

    game->def_transtion_to(elback_arrow, title);

    // シーンの処理をスタートさせる。最初に表示したいシーンのstart()を呼び出すこと
    title->start(window);

    // Title_scene ts(window);

    glfwTerminate();
    return 0;
}