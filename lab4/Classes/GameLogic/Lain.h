#pragma once

#include "Enemy.h"
#include "WaveManager.h"
#include "EnemyManager.h"
#include "MainGame.h"

class MainGame;

///A place from where enemies are comming.
class Lain {

    EnemyManager enemy_manager;

    void spawnEnemy(const Enemy::Ptr& enemy, MainGame* instance);

    /// Time when last enemy was spawned.
    sf::Clock last_enemy_spawned;

    /// Path from that lain to a castle.
    Path path;

public:

    Lain() = default;

    EnemyManager *getEnemyManager();

    void update();

    void spawnEnemies(WaveManager &wave_manager, MainGame* instance);

    void draw(sf::RenderTarget &target) const;

    void setPath(unsigned int num);
};

