#include "SBFW/sbfw.hpp"
#include <DataOf2D.hpp>

#include <stgview/GameScene.hpp>
#include <stgview/ResultScene.hpp>

#include <internal/card/ChangeStructure.hpp>

#include "filename.hpp"
using namespace std;
class functor {
  private:
    int idx;

  public:
    static int selected_key;
    functor(int idx) : idx(idx) {}
    void operator()() { selected_key = idx; }
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
struct ResultSceneElemInfos {
    sbfw::ElemInfo retry{{-0.75, -0.75}, "DarkBlue/Button/retry.png", 0.9f};
    sbfw::ElemInfo set{{-0.25, -0.75}, "DarkBlue/Button/set.png", 0.9f};
    sbfw::ElemInfo home{{0.25, -0.75}, "DarkBlue/Button/home.png", 0.9f};
    sbfw::ElemInfo end{{0.75, -0.75}, "DarkBlue/Button/end.png", 0.9f};

} res_ei;
int main() {
    sbfw::InitSBFW(800, 700);
    // internalとの結合を行う
    ChangeStructure cs;

    /******************
     * 画面に登場する要素の定義
     *******************/
    // コンストラクタは(設置位置,画像ファイル名,倍率)
    // 画像ファイル名はimgにあること前提
    // 設置位置は中心を0,0とし、左端をx=-1, 右端をx=1とする
    sbfw::ElemInfo elgo_battle(sbfw::ToRegularXYpos(400, 350),
                               "DarkBlue/Button/GoGame.png", 0.8);
    sbfw::ElemInfo elgo_select({0, -0.5}, "DarkBlue/Button/GoSelectCard.png",
                               0.8);
    sbfw::ElemInfo elgo_title({0, -0.7}, "test_img/go_title.png", 0.2);
    vector<sbfw::ElemInfo> card_img_in_battle(3);
    for(int i = 0; i < 3; i++) {
        card_img_in_battle[i] = sbfw::ElemInfo(
            {0.45f, -0.4f + -0.4f * i + 0.4f}, "ic_launcher.png", 1.0);
    }
    vector<sbfw::ElemInfo> card_img_in_result(3);
    for(int i = 0; i < 3; i++) {
        card_img_in_result[i] =
            sbfw::ElemInfo({-0.8f + 0.2f * i, -0.4f}, "ic_launcher.png", 0.7);
    }
    vector<sbfw::ElemInfo> el_allocate(3);
    auto ToFileName = [](string s) { return "card/" + s + ".png"; };
    auto yy = cs.callSet3Cards();
    for(int i = 0; i < 3; i++)
        el_allocate[i] = sbfw::ElemInfo({-0.6f + i * 0.6f, 0.3f},
                                        ToFileName(yy[i].cardName));

    struct ElementDefnition {
        sbfw::ElemInfo boss{{0, 0.5}, "status/redstar.png", 3};
        sbfw::ElemInfo fighter{{0.2, 0.2}, "battle/me.png", 5};
        sbfw::ElemInfo back_arrow{{-0.7, -0.8}, "DarkBlue/Button/back.png"};
        sbfw::ElemInfo OK{{0.7, -0.8}, "DarkBlue/Button/ok.png"};
    } el_general;
    struct ElementDefnitionForSelectSubScene {
        sbfw::ElemInfo left_arrow{
            {-0.2, -0.8}, "DarkBlue/arrows/left.png", 0.8};
        sbfw::ElemInfo right_arrow{
            {0.2, -0.8}, "DarkBlue/arrows/right.png", 0.8};
    } el_sub_select;

    vector<sbfw::ElemInfo> elcards(card_fnames.size());
    int columns = 4, sub_scene_num = 3, each_scene_num = 12;
    printf("%d, %d\n", each_scene_num, card_fnames.size());
    float sx = -0.7, sy = 0.7; // 31 = 12 + 12 + 7;
    auto x = cs.callHasAllCards();
    int card_num = x.size();

    for(int i = 0; i < x.size(); i++) {
        int one_scene_idx = i % each_scene_num;
        DataOf2D d = {sx + one_scene_idx % columns * 0.4f,
                      sy - one_scene_idx / columns * 0.4f};
        // string card_fname =
        //     "ansicard/" + true_card_fname[japanese_card_fnames[i]];
        string card_fname = "card/" + x[i].cardName + ".png";
        cout << "this is call all cards" << x[i].cardName << endl;
        elcards[i] = sbfw::ElemInfo(d, card_fname, 0.6);
    }

    /******************
     * 以下はシーンの準備
     *******************/
    auto [title, select, score] =
        sbfw::scene::prepare_scenes<3>();        // 構造化束縛で1つずつ
    auto sub = sbfw::scene::prepare_scenes<3>(); // 配列arrayで受け取る
    // auto [game] = sbfw::scene::prepare_scenes<BattleScene, 1>();
    auto [result] = sbfw::scene::prepare_scenes<stgview::ResultScene, 1>();
    auto [game] = sbfw::scene::prepare_scenes<stgview::GameScene, 1>();

    title->SetWindowName("title");
    select->SetWindowName("select");
    sub[0]->SetWindowName("sub[0]");
    sub[1]->SetWindowName("sub[1]");
    sub[2]->SetWindowName("sub[2]");
    game->SetWindowName("game");
    result->SetWindowName("Result");
    score->SetWindowName("score");

    auto select_sub_init_func = [&]() {
        cs = ChangeStructure();

        auto x = cs.callHasAllCards();
        int card_num = x.size();

        for(int i = 0; i < x.size(); i++) {
            int one_scene_idx = i % each_scene_num;
            DataOf2D d = {sx + one_scene_idx % columns * 0.4f,
                          sy - one_scene_idx / columns * 0.4f};
            string card_fname = "card/" + x[i].cardName + ".png";
            elcards[i] = sbfw::ElemInfo(d, card_fname, 0.6);
        }

        for(int i = 0; i < card_num; i++) {
            switch(i / each_scene_num) {
            case 0:
                sub[0]->AddButton(elcards[i], functor(x[i].id));
                break;
            case 1:
                sub[1]->AddButton(elcards[i], functor(i));
                break;
            case 2:
                sub[2]->AddButton(elcards[i], functor(i));
                break;
            default:
                break;
            }
        }
    };
    sub[0]->SetInitFunc(select_sub_init_func);
    sub[1]->SetInitFunc(select_sub_init_func);
    sub[2]->SetInitFunc(select_sub_init_func);

    /******************
     * シーンに要素=button or imageを貼り付ける
     *******************/

    for(int i = 0; i < card_num; i++) {
        switch(i / each_scene_num) {
        case 0:
            sub[0]->AddButton(elcards[i], functor(x[i].id));
            break;
        case 1:
            sub[1]->AddButton(elcards[i], functor(x[i].id));
            break;
        case 2:
            sub[2]->AddButton(elcards[i], functor(x[i].id));
            break;
        default:
            break;
        }
    }

    // vector<sbfw::ElemKey> alloc_key_in_gamescene(3);
    // for(int i = 0; i < 3; i++) {
    //     alloc_key_in_gamescene[i] = game->AddImage(card_img_in_battle[i]);
    // }

    vector<sbfw::ElemKey> alloc_key(3);
    for(int i = 0; i < 3; i++) {
        select->DefTranstionTo(el_allocate[i], sub[0]);
        alloc_key[i] = select->AddButton(el_allocate[i], allocator_btn_pos(i));
    }
    select->AddButton(el_general.OK, [&]() {
        if(!cs.registerStructure()) {
            cout << "this combination is not ok" << endl;
        }
    });
    CardHas ch;

    sub[0]->AddButton(el_general.OK, [&]() {
        select->ChangeImage(
            alloc_key[allocator_btn_pos::selected_key],
            sbfw::ElemInfo({1, 1}, "card/" +
                                       ch.getCardName(functor::selected_key) +
                                       ".png"));
        cs.ChangeStructureCard(allocator_btn_pos::selected_key,
                               functor::selected_key);
    });
    sub[1]->AddButton(el_general.OK, [&]() {
        select->ChangeImage(
            alloc_key[allocator_btn_pos::selected_key],
            sbfw::ElemInfo({1, 1}, "card/" +
                                       ch.getCardName(functor::selected_key) +
                                       ".png"));
        cs.ChangeStructureCard(allocator_btn_pos::selected_key,
                               functor::selected_key);
    });
    sub[2]->AddButton(el_general.OK, [&]() {
        select->ChangeImage(
            alloc_key[allocator_btn_pos::selected_key],
            sbfw::ElemInfo({1, 1}, "card/" +
                                       ch.getCardName(functor::selected_key) +
                                       ".png"));
        cs.ChangeStructureCard(allocator_btn_pos::selected_key,
                               functor::selected_key);
    });

    game->result_scene = result;

    title->DefTranstionTo(elgo_select, select);
    title->DefTranstionTo(elgo_battle, game);
    select->DefTranstionTo(el_general.back_arrow, title);

    sub[0]->DefTranstionTo(el_general.back_arrow, select);
    sub[0]->DefTranstionTo(el_general.OK, select);
    sub[0]->DefTranstionTo(el_sub_select.right_arrow, sub[1]);

    sub[1]->DefTranstionTo(el_general.back_arrow, select);
    sub[1]->DefTranstionTo(el_general.OK, select);
    sub[1]->DefTranstionTo(el_sub_select.right_arrow, sub[2]);
    sub[1]->DefTranstionTo(el_sub_select.left_arrow, sub[0]);

    sub[2]->DefTranstionTo(el_general.back_arrow, select);
    sub[2]->DefTranstionTo(el_general.OK, select);
    sub[2]->DefTranstionTo(el_sub_select.left_arrow, sub[1]);

    result->DefTranstionTo(res_ei.home, title);
    result->DefTranstionTo(res_ei.retry, game);
    result->DefTranstionTo(res_ei.set, select);
    result->DefTranstionTo(res_ei.end, sbfw::scene::program_terminate);

    // シーンの処理をスタートさせる。最初に表示したいシーンのstart()を呼び出すこと
    title->Start();
    // result->Start();

    sbfw::TerminateSBFW();
    return 0;
}
