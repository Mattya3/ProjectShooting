#include <stgview/GameScene.hpp>

#include <SBFW/unit.hpp>

#include <bits/stdc++.h>
using namespace std;
namespace stgview {
void GameScene::layer_front() {
    // 戦闘画面の背景 灰色
    draw::RectFilled(leftup.x, rightdown.x, leftup.y, rightdown.y,
                     {0.2, 0.2, 0.2});

    // 戦闘描写 自機、敵、弾
    CombineInternalBattle();

    // ステータス系
    life_point.Draw(bt.viewer.callHp());
    number_display.Draw(bt.viewer.callExp(), {0.3f, 0.6f}, 1.0, 0.5);
    number_display.Draw(bt.viewer.callNeedExp(), {0.8f, 0.25f}, 0.75, 3);

    // ゲームオーバ時には1.5秒静止して、リザルトへ
    if(is_gameover) {
        this_thread::sleep_for(chrono::milliseconds(1500));
        GoNextScene(result_scene);
    }
}
void GameScene::CombineInternalBattle() {
    bt.timer();
    bt.inputMoving(wp, ap, sp, dp);
    auto x = bt.viewer.callHero();
    DrawRotatedMyfighter(x);

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

    if(bt.viewer.callHp() <= 0) {
        is_gameover = true;
    }
}
void GameScene::key_callback(GLFWwindow *window, int key, int scancode,
                             int action, int mods) {
    auto control_key_flag = [&](int key_id, bool &flag) {
        if(key == key_id) {
            if(action == GLFW_PRESS) {
                flag = true;
            } else if(action == GLFW_RELEASE) {
                flag = false;
            }
        }
    };
    control_key_flag(GLFW_KEY_W, wp);
    control_key_flag(GLFW_KEY_A, ap);
    control_key_flag(GLFW_KEY_S, sp);
    control_key_flag(GLFW_KEY_D, dp);
    control_key_flag(GLFW_KEY_SPACE, spacep);
    bt.inputShooting(spacep);

    if(key == GLFW_KEY_J && action == GLFW_PRESS) {
        bt.inputLevelUp(0);
    }
    if(key == GLFW_KEY_K && action == GLFW_PRESS) {
        bt.inputLevelUp(1);
    }
    if(key == GLFW_KEY_L && action == GLFW_PRESS) {
        bt.inputLevelUp(2);
    }
    if(key == GLFW_KEY_E && action == GLFW_PRESS) {
        bt.inputBomb();
    }
    if(key == GLFW_KEY_Q && action == GLFW_PRESS) {
        bt.inputSpeed();
    }
}

void GameScene::InitAfterTransition() {
    bt.start(0);
    is_gameover = false;
    auto card_img = bt.viewer.callCard();
    for(int i = 0; i < 3; i++) {
        AddImage("card/" + card_img[i].cardName + ".png",
                 {0.45f, -0.4f + -0.4f * i + 0.4f});
    }
}

void GameScene::DrawRotatedMyfighter(GamePointMono x) {
    float rotate = x.keyNum * 180 / M_PI;
    auto l = to_Location(x);
    glPushMatrix();
    glTranslatef(l.sx + l.xlen / 2, l.sy + l.ylen / 2, 0);
    glRotatef(rotate, 0, 0, 1);
    glTranslatef(-l.sx - l.xlen / 2, -l.sy - l.ylen / 2, 0);
    myfighter.view_clone(l);
    glPopMatrix();
}
} // namespace stgview