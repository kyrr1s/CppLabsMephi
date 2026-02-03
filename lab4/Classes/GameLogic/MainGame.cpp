#include "MainGame.h"

#include <functional>

/**
 * @brief Updates a main game, its weapon managers and lains.
 */

void MainGame::update() {
    for (auto &it : lains) {
        it.update();
        weapon_manager.update();
        it.spawnEnemies(wave_manager, this);
        weapon_manager.handleEnemyLockOn(it.getEnemyManager());
    }
}

/**
 * @brief Adds gold.
 */

void MainGame::addGold(unsigned int amount) {
    gold += amount;
}

/**
 * @brief Substracts gold.
 */

void MainGame::substractGold(unsigned int amount) {
    if (amount > gold) {
        gold = 0;
        return;
    }
    gold -= amount;
}

/**
 * @brief Sets gold.
 */

void MainGame::setGold(unsigned int amount) {
    gold = amount;
}

/**
 * @return Gold of a player.
 */

unsigned int MainGame::getGold() const {
    return gold;
}

/**
 * @return Weapon manager.
 */

WeaponManager * MainGame::getWeaponManager() {
    return &weapon_manager;
}

/**
 * @return Wave manager.
 */

WaveManager * MainGame::getWaveManager() {
    return &wave_manager;
}

/**
 * @brief Callback for a main game when sm enemy is killed.
 * @param enemy - enemy that should be killed.
 */

void MainGame::onEnemyKilled(const Enemy::Ptr &enemy) {
    for (auto& it: lains) {
        it.getEnemyManager()->removeEnemy(enemy);
    }
    addGold(wave_manager.getCurrentWaveNo() * 5 + 5);
}

/**
 * @brief Call back for a main game when sm enemy reaches a castle.
 * @param enemy - enemy that reaches a castle.
 */

void MainGame::onEnemyDestination(const Enemy::Ptr &enemy) {
    castle.substractHealth(enemy->getHealth());
    for (auto &it: lains) {
        it.getEnemyManager()->removeEnemy(enemy);
    }
}

/**
 * @return a Castle object.
 */

Castle MainGame::getCastle() const {
    return castle;
}

/**
 * @return a Lains object.
 */

std::vector<Lain> MainGame::getLains() const {
    return lains;
}

/**
 * @brief Checks if that tile can be compressed into one point or not.
 * @param vec - a vector if tiles
 * @param x - a left bound of that tile.
 * @param y - a right bound of that tile.
 */

bool MainGame::canBeCompressedTile(const std::vector<Tile>& vec, int x, int y) {
    bool first = false, second = false, third = false;
    for (const auto& tile: vec) {
        if (tile.getType() == typePath && tile.getX() == x+tile.TILE_SIZE && tile.getY() == y)
            first = true;
        if (tile.getType() == typePath && tile.getX() == x && tile.getY() == y+tile.TILE_SIZE)
            second = true;
        if (tile.getType() == typePath && tile.getX() == x+tile.TILE_SIZE && tile.getY() == y+tile.TILE_SIZE)
            third = true;
    }
    return first && second && third;
}

/**
 * @brief Sets a path from tile vector.
 * @param vec -  a vector if tiles.
 */

void MainGame::setPath(const std::vector<Tile>& vec) {
    int count_lains_tiles = 0;
    std::vector<sf::Vector2<int>> compressed_tiles;
    std::vector<sf::Vector2<int>> pathing_points;
    for (const auto& tile : vec) {
        if (tile.getType() == typeLain)
            count_lains_tiles++;
        if (canBeCompressedTile(vec, tile.getX(), tile.getY()))
            compressed_tiles.emplace_back(tile.getX()+tile.TILE_SIZE, tile.getY()+tile.TILE_SIZE);
    }
    int count_lains = count_lains_tiles/4;
    for (int i = 0; i < count_lains; ++i) {
        lains.emplace_back();
    }

    lains[0].setPath(0);
    lains[1].setPath(1);
    //hardcode

}

/**
 * @brief Changes a wave.
 */

void MainGame::nextWave() {
    wave_manager.forceWave();
}






