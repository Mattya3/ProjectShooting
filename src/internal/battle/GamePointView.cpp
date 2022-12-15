#include <internal/battle/GamePointView.hpp>

GamePointMono GamePointView::callHero(){
    return hero;
}
    
vector<GamePointMono> GamePointView::callEnemy(){
    return enemies;
}

vector<GamePointMono> GamePointView::callHeroBullet(){
    return heroBullets;
}

vector<GamePointMono> GamePointView::callHeroBullet(){
    return enemyBullets;
}

void GamePointView::putHero(HeroPoint h){
    GamePointMono bullet;
    heroBullets.clear();
    hero.position = h.position;
    hero.size = h.size;
    hero.direction = h.direction;
    for(int i = 0; i < h.bullets.size(); i++){
        bullet.position = h.bullets.at(i).position;
        bullet.size = h.bullets.at(i).size;
        heroBullets.push_back(bullet);
    }
}

void GamePointView::putEnemy(vector<EnemyPoint> e){
    GamePointMono bullet;
    enemies.clear();
    enemyBullets.clear();
    for(int i = 0; e.size(); i++){
        enemy.position = e.at(i).position;
        enemy.size = e.at(i).size;
        enemy.size = e.at(i).id;
        enemies.push_back(enemy);
        for(int j = 0; j < h.bullets.size(); j++){
            bullet.position = e.at(i).bullets.at(j).position;
            bullet.size = e.at(i).bullets.at(j).size;
            enemyBullets.push_back(bullet);
        }
    }
}