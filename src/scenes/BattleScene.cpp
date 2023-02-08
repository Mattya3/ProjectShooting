#include <component/Button_anyTimes.hpp>
#include <component/Image.hpp>
#include <component/NextSceneButton.hpp>
#include <scenes/BattleScene.hpp>
#include <scenes/ResolverCallbackFunc.hpp>
// #include <scenes/Title_Scene.hpp>

#include <DataOf2D.hpp>

void filled_view(Location l, float r, float g, float b) {
    glBegin(GL_POLYGON);
    glColor3d(r, g, b);
    glVertex2d(l.sx, l.sy);
    glVertex2d(l.sx + l.xlen, l.sy);
    glVertex2d(l.sx + l.xlen, l.sy + l.ylen);
    glVertex2d(l.sx, l.sy + l.ylen);
    glEnd();
}

void show_point(double x, double y, char c) {
    glBegin(GL_POLYGON);
    if(c == 'R') {
        glColor3d(1.0, 0.0, 0.0);
    } else if(c == 'G') {
        glColor3d(0.0, 1.0, 0.0);
    } else if(c == 'B') {
        glColor3d(0.0, 0.0, 1.0);
    }

    glVertex2d(x, y);
    glVertex2d(x + 0.01, y);
    glVertex2d(x + 0.01, y + 0.01);
    glVertex2d(x, y + 0.01);
    glEnd();
}



void BattleScene::key_callback(GLFWwindow *window, int key, int scancode,
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

    if(key == GLFW_KEY_R && action == GLFW_PRESS) {
        // rotate_my_fighter();
        life.decrement_stock();
    }
    if(key == GLFW_KEY_J && action == GLFW_PRESS) {
        bt.inputLevelUp(0);
    }
    if(key == GLFW_KEY_K && action == GLFW_PRESS) {
        bt.inputLevelUp(1);
    }
    if(key == GLFW_KEY_L && action == GLFW_PRESS) {
        bt.inputLevelUp(2);
    }
}

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