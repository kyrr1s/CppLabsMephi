#include "Lain.h"
#include "MainGame.h"

/**
 * @brief Updates enemy manager of that lain.
 */

void Lain::update() {
    enemy_manager.update();
    enemy_manager.handleEnemyPathing(path);
}

/**
 * @brief Spawn enemies from that lain.
 * @param wave_manager - Wave manager for that lain.
 * @param instance - Main Game menu ptr.
 */

void Lain::spawnEnemies(WaveManager& wave_manager, MainGame* instance) {
    // We need to check if we are eligible to spawn enemies or not.
    Wave *wave = wave_manager.getCurrentWave();
    const unsigned int spawnInterval = wave->getEnemySpawnInterval();

    if (last_enemy_spawned.getElapsedTime().asMilliseconds() >= spawnInterval && wave->getEnemyCount() > 0) {
        wave->enemyGotSpawned();
        last_enemy_spawned.restart();

        // Each wave, our enemies will have 5 more health.
        spawnEnemy(std::make_shared<Enemy>(wave_manager.getCurrentWaveNo() * 20 + 30, "Slime"), instance);
    }
}

/**
 * @brief Draws every enemy from that lain.
 * @param target - an SFML object that will draw.
 */

void Lain::draw(sf::RenderTarget& target) const {
    enemy_manager.draw(target);
}

/**
 * @brief Spawn an enemy.
 * @param enemy - an enemy that will be spawned.
 * @param instance - a Main Game ptr.
 */

void Lain::spawnEnemy(const Enemy::Ptr &enemy, MainGame* instance) {
    enemy_manager.addEnemy(enemy);

    const sf::Vector2i spawnLocation = path.getEnemySpawnTileCoordinate();
    //const sf::Vector2f windowPosition = path.getTileWindowPositionFromTileCoordinate(spawnLocation);
    const sf::Vector2f windowPosition = {static_cast<float>(spawnLocation.x), static_cast<float>(spawnLocation.y)};

    enemy->setPosition(windowPosition.x, windowPosition.y);
    enemy->setGoalHandler(std::bind(&MainGame::onEnemyDestination, instance, std::placeholders::_1));
    enemy->setEnemyDeadHandler(std::bind(&MainGame::onEnemyKilled, instance, std::placeholders::_1));
}

/**
 * @return Enemy manager of that lain.
 */

EnemyManager *Lain::getEnemyManager() {
    return &enemy_manager;
}

/**
 * @brief Sets a path for that lain.
 * @param num - a number of path.
 */

void Lain::setPath(unsigned int num) {
    path.initialize(num);
}