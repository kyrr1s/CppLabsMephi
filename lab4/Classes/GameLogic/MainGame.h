#pragma once

#include "Weapon.h"
#include "WeaponManager.h"
#include "Castle.h"
#include "Lain.h"

#include <memory>
#include <functional>


//! An engine of a game logic.
class MainGame {

    /// Initial gold = 1000
    unsigned int gold = 1000;

    /// Handles a health of a player
    Castle castle;

    /// Handles waves
    WaveManager wave_manager;

    /// Contaiters for enemies
    std::vector<class Lain> lains;

    /// Weapon handler
    WeaponManager weapon_manager;

    /// Checks if tile can be compressed
    bool canBeCompressedTile(const std::vector<Tile> &vec, int x, int y);

public:

    void update();

    void addGold(unsigned int amount);

    void substractGold(unsigned int amount);

    void setGold(unsigned int amount);

    [[nodiscard]] unsigned int getGold() const;

    WeaponManager * getWeaponManager();

    [[nodiscard]] WeaponManager * getWeaponManagerToDraw() {
        return &weapon_manager;
    }

    void onEnemyKilled(const Enemy::Ptr &enemy);

    void onEnemyDestination(const Enemy::Ptr &enemy);

    [[nodiscard]] Castle getCastle() const;

    [[nodiscard]] std::vector<Lain> getLains() const;

    void setPath(const std::vector<Tile>& vec);

    void nextWave();

    WaveManager *getWaveManager();
};

