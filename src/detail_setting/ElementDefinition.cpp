// #include <detail_setting/ElementDefinition.hpp>

//     sbfw::ElemInfo elgo_battle({0, 0.5}, "title/goBattle.png", 0.3);
//     sbfw::ElemInfo elgo_select({0, -0.5}, "title/goSelectCard.png", 0.3);
//     sbfw::ElemInfo elgo_back({-0.5, -0.5}, "test_img/go_title.png");
//     vector<sbfw::ElemInfo> card_img_in_battle(3);
//     for(int i = 0; i < 3; i++) {
//         card_img_in_battle[i] =
//             sbfw::ElemInfo({0.25f, -0.4f + -0.2f * i}, "ic_launcher.png", 0.5);
//     }
//     vector<sbfw::ElemInfo> el_allocate(3);
//     for(int i = 0; i < 3; i++)
//         el_allocate[i] =
//             sbfw::ElemInfo({-0.6f + i * 0.6f, 0.3f}, "ic_launcher.png");

//     struct ElementDefnition {
//         sbfw::ElemInfo boss{{0, 0.5}, "status/redstar.png", 3};
//         sbfw::ElemInfo fighter{{0.2, 0.2}, "battle/me.png", 5};
//         sbfw::ElemInfo back_arrow{{-0.7, -0.7}, "test_img/back.png", 0.2};
//         sbfw::ElemInfo OK{{0.8, -0.8}, "select_card_sub/OK.png", 0.3};

//     } el_general;
//     struct ElementDefnitionForSelectSubScene {
//         sbfw::ElemInfo left_arrow{
//             {-0.2, -0.8}, "select_card_sub/leftarrow.png", 0.4};
//         sbfw::ElemInfo right_arrow{
//             {0.2, -0.8}, "select_card_sub/rightarrow.png", 0.4};
//     } el_sub_select;

//     vector<sbfw::ElemInfo> elcards(card_fnames.size());
//     int card_num = elcards.size();
//     int columns = 4, sub_scene_num = 3, each_scene_num = 12;
//     printf("%d, %d\n", each_scene_num, card_fnames.size());
//     float sx = -0.7, sy = 0.7; // 31 = 12 + 12 + 7;
//     for(int i = 0; i < card_num; i++) {
//         int one_scene_idx = i % each_scene_num;
//         DataOf2D d = {sx + one_scene_idx % columns * 0.4f,
//                       sy - one_scene_idx / columns * 0.4f};
//         elcards[i] = sbfw::ElemInfo(d, "card/" + card_fnames[i], 0.6);
//     }