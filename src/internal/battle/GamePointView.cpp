#include <internal/battle/GamePointView.hpp>

int GamePointView::callHp(){
    return heroHasHp;
}

int GamePointView::callScore(){
    return score;
}

int GamePointView::callNeedEXP(){
    return needLevelUpEXP;
}

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

vector<GameCardMono> GamePointView::callCard(){
    return cards;
}

void GamePointView::putScore(int get){
    score = get;
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
    heroHasHp = h.nowHP;
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

void GamePointView::putCard(vector<Card> l){
    GameCardMono card;
    for(int i = 0; i < l.size(); i++){
        card.cardName = l.at(i).cardName;
        card.cardLevel = 1;
        if(card.cardName == "未セット") card.needEXP = -1;
        else card.needEXP = l.at(i).needEXP;
        needLevelUpEXP += l.at(i).needEXP;
        cards.push_back(card);
    }
}

void GamePointView::putCardLevel(int number, int count){
    cards.at(number).cardLevel++;
    if(count <= 0) cards.at(number).needEXP = -1;
}