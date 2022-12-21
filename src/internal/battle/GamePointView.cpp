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

vector<GamePointMono> GamePointView::callEnemyBullet(){
    return enemyBullets;
}

void GamePointView::putHero(HeroPoint h, vector<BulletPoint> b){
    GamePointMono bullet;
    heroBullets.clear();
    hero.position = h.position;
    hero.size = h.size;
    hero.keyNum = h.direction;
    for(int i = 0; i < b.size(); i++){
        bullet.position = b.at(i).position;
        bullet.size = b.at(i).size;
        heroBullets.push_back(bullet);
    }
}

void GamePointView::putEnemy(vector<EnemyPoint> e, vector<BulletPoint> b){
    GamePointMono bullet;
    GamePointMono enemy;
    enemies.clear();
    enemyBullets.clear();
    for(int i = 0; i < e.size(); i++){
        enemy.position = e.at(i).position;
        enemy.size = e.at(i).size;
        enemy.keyNum = e.at(i).id;
        enemies.push_back(enemy);
    }
    for(int i = 0; i < b.size(); i++){
        bullet.position = b.at(i).position;
        bullet.size = b.at(i).size;
        enemyBullets.push_back(bullet);
    }
}

