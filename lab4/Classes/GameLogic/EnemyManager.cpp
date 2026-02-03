#include "EnemyManager.h"
#include <iostream>

/**
 * @brief Sets enemy texture.
*/
EnemyManager::EnemyManager() {
    enemy_textures_coords["Slime"] = {944, 0, 16, 16};
    enemy_tileset.loadFromFile("assets/Level1/AllAssetsPreview.png");
}

/**
 * @brief Delete enemy from a game.
 */

void EnemyManager::removeEnemy(const Enemy::Ptr &enemy) {
    if (std::find(enemies.begin(), enemies.end(), enemy) != enemies.end())
        enemies_after_step.push_back(enemy);
}

/**
 * @brief Adds enemy on a window
 */

void EnemyManager::addEnemy(const Enemy::Ptr &enemy) {
    enemy->setTexture(enemy_tileset, enemy_textures_coords["Slime"]);
    enemies.push_back(enemy);
}

/**
 * @brief Steps every enemy and tick's their effects.
 */

void EnemyManager::update() {
    for (const auto &enemy : enemies) {
        enemy->step();
        enemy->tickEffect();
    }

    cleanUp();
}

/**
 * @brief Draw all enemies.
 * @param target - An SFML object that draws.
 */

void EnemyManager::draw(sf::RenderTarget& target) const {
    for (const auto& enemy: enemies)
        target.draw(*enemy, sf::RenderStates::Default);
}

/**
 * @return An emount of enemies on a board.
 */

std::size_t EnemyManager::getEnemyCount() {
    return enemies.size();
}

/**
 * @brief Sets enemy's health, name and sprite.
 * @param path - a Path object, which is used for tracking enemies.
 */

void EnemyManager::handleEnemyPathing(const Path &path) {
    for (const auto &enemy : enemies) {
        if(!enemy->needsNewPath())
            continue;

        const sf::Vector2<int> targetTileCoordinate = path.getEnemyPathTileCoordinate(enemy->getPathingIndex() + 1);
        const sf::Vector2<float> targetPosition = {static_cast<float>(targetTileCoordinate.x), static_cast<float>(targetTileCoordinate.y)};

        if (sf::Vector2<float>({targetPosition.x, targetPosition.y}) == enemy->getPosition()) {
            // enemy reached destination
            enemy->reachGoal();
        }

        const Direction direction = path.determineDirection(enemy->getPosition(),
                                                           {targetPosition.x, targetPosition.y});

        enemy->setDirection(direction, {targetPosition.x, targetPosition.y});
    }
}

/**
 * @brief Checks what enemies should be erased after step.
 */

void EnemyManager::cleanUp() {

    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [this](const Enemy::Ptr &enemy) {
        return std::find(enemies_after_step.begin(), enemies_after_step.end(), enemy) != enemies_after_step.end();
    }), enemies.end());

    enemies_after_step.clear();
}

/**
 * @brief Checks if weapon should have a new lock on the closest enemy.
 */

void EnemyManager::tryGetLockOn(const Weapon::Ptr &weapon) {
    if (weapon->hasLockOn())
        return;

    auto it = std::find_if(enemies.begin(), enemies.end(), [weapon](const Enemy::Ptr& enemy) {
        return weapon->isInRange(enemy);
    });

    if (it == enemies.end())
        return;

    weapon->lockOn(*it);
}