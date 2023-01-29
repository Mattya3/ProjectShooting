// #include <scenes/Title_Scene.hpp>
#include <setting.hpp>
using namespace std;
#include "SBFW/sbfw.hpp"
#include "filename.hpp"
#include <scenes/BattleScene.hpp>



class functor {
  private:
    int idx;

  public:
    static int selected_key;
    functor(int idx) : idx(idx) {}
    void operator()() {
        cout << "You Select " << idx << endl;
        selected_key = idx;
    }
};

class allocator_btn_pos {
  private:
    int idx;

  public:
    static int selected_key;
    allocator_btn_pos(int idx) : idx(idx) {}
    void operator()() { selected_key = idx; }
};
int functor::selected_key = 0;
int allocator_btn_pos::selected_key = 0;

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
    // sbfw::ElemInfo eldroid({-0.5, 0.3}, "ic_launcher.png");
    // sbfw::ElemInfo eldroid2({+0.5, 0.3}, "ic_launcher.png");
    vector<sbfw::ElemInfo> eldroid(3);
    for(int i = 0; i < 3; i++) {
        eldroid[i] =
            sbfw::ElemInfo({0.35f + i * 0.2f, -0.7f}, "ic_launcher.png", 0.5);
    }

    vector<sbfw::ElemInfo> el_allocate(3);
    for(int i = 0; i < 3; i++)
        el_allocate[i] =
            sbfw::ElemInfo({-0.6f + i * 0.6f, 0.3f}, "ic_launcher.png");

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

    auto [title, select, score] =
        sbfw::scene::prepare_scenes<3>();        // 構造化束縛で1つずつ
    auto sub = sbfw::scene::prepare_scenes<3>(); // 配列arrayで受け取る
    auto [game] =
        sbfw::scene::prepare_scenes<BattleScene, 1>(); // ユーザ定義のSceneもok
    title->set_window_name("title");
    select->set_window_name("select");
    sub[0]->set_window_name("sub[0]");
    sub[1]->set_window_name("sub[1]");
    sub[2]->set_window_name("sub[2]");

    game->set_window_name("game");
    score->set_window_name("score");

    for(int i = 0; i < card_num; i++) {
        switch(i / each_scene_num) {
        case 0:
            sub[0]->add_button(elcards[i], functor(i));
            break;
        case 1:
            sub[1]->add_button(elcards[i], functor(i));
            break;
        case 2:
            sub[2]->add_button(elcards[i], functor(i));
            break;
        default:
            break;
        }
    }

    title->def_transtion_to(elgo_select, select);
    title->def_transtion_to(elgo_battle, game);

    select->def_transtion_to(elback_arrow, title);

    vector<sbfw::ElemKey> alloc_key_in_gamescene(3);
    for(int i = 0; i < 3; i++) {
        alloc_key_in_gamescene[i] = game->add_image(eldroid[i]);
    }

    vector<sbfw::ElemKey> alloc_key(3);
    for(int i = 0; i < 3; i++) {
        select->def_transtion_to(el_allocate[i], sub[0]);
        alloc_key[i] = select->add_button(el_allocate[i], allocator_btn_pos(i));
    }

    sub[0]->def_transtion_to(elback_arrow, select);
    sub[0]->def_transtion_to(elOK, select);
    sub[0]->def_transtion_to(elright_arrow, sub[1]);
    sub[0]->add_button(elOK, [&]() {
        select->change_image(alloc_key[allocator_btn_pos::selected_key],
                             elcards[functor::selected_key]);
        game->change_image(
            alloc_key_in_gamescene[allocator_btn_pos::selected_key],
            elcards[functor::selected_key]);
    });
    sub[1]->def_transtion_to(elback_arrow, select);
    sub[1]->def_transtion_to(elOK, select);
    sub[1]->def_transtion_to(elright_arrow, sub[2]);
    sub[1]->def_transtion_to(elleft_arrow, sub[0]);
    sub[1]->add_button(elOK, [&]() {
        select->change_image(alloc_key[allocator_btn_pos::selected_key],
                             elcards[functor::selected_key]);
        game->change_image(
            alloc_key_in_gamescene[allocator_btn_pos::selected_key],
            elcards[functor::selected_key]);
    });

    sub[2]->def_transtion_to(elback_arrow, select);
    sub[2]->def_transtion_to(elOK, select);
    sub[2]->def_transtion_to(elleft_arrow, sub[1]);
    sub[2]->add_button(elOK, [&]() {
        select->change_image(alloc_key[allocator_btn_pos::selected_key],
                             elcards[functor::selected_key]);
        game->change_image(
            alloc_key_in_gamescene[allocator_btn_pos::selected_key],
            elcards[functor::selected_key]);
    });

    // game->def_transtion_to(elback_arrow, title);
    // game->add_image()

    // シーンの処理をスタートさせる。最初に表示したいシーンのstart()を呼び出すこと
    title->start(window);

    glfwTerminate();
    return 0;
}