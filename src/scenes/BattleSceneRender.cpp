#include <scenes/BattleScene.hpp>

void BattleScene::render_dynamic_view() {
    auto x = bt.viewer.callHero();
    view_rotated_myfighter(x);

    bt.viewer.callEnemy();
    auto d = bt.viewer.callHeroBullet();
    for(auto &&i : d) {
        mybullet.view_clone(to_Location(i, i.size, i.size));
    }

    auto en = bt.viewer.callEnemy();
    for(auto &&i : en) {
        enemy_tex.view_clone(to_Location(i, i.size, i.size));
    }

    auto ebs = bt.viewer.callEnemyBullet();
    for(auto &&i : ebs) {
        ene_bullet.view_clone(to_Location(i, i.size, i.size));
    }

    operate_my_fighter(wp, ap, sp, dp);

    if(bt.viewer.callHp() < 0) {
        game_end_time = now_time;
        is_gameover = true;

        buf_hero = x;
        buf_enemy = en;
        buf_hero_bullet = d;
        buf_enemy_bullet = ebs;
    }
}
void BattleScene::render_game_over() {
    view_rotated_myfighter(buf_hero);

    for(auto &&i : buf_hero_bullet) {
        mybullet.view_clone(to_Location(i, i.size, i.size));
    }

    for(auto &&i : buf_enemy) {
        enemy_tex.view_clone(to_Location(i, i.size, i.size));
    }

    for(auto &&i : buf_enemy_bullet) {
        ene_bullet.view_clone(to_Location(i, i.size, i.size));
    }
}
void BattleScene::render_static_view() {}