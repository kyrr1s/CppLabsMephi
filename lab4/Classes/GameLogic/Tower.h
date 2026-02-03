#pragma once

#include "ElementType.h"
#include "Enemy.h"
#include "Weapon.h"
#include "TileType.h"

#include <memory>
#include <vector>

//! Tower that shoots.
class Tower : public Weapon {

    /// Current level of a tower.
    int level = 1;

    /// Fire rate of the tower, in milliseconds.
    /// 1000 means 1 projectile a second
    /// 500 means 2 projectiles a second...
    unsigned int fire_rate;

    /// Last time this tower shot.
    sf::Clock timeof_last_shot;

    std::map<int, std::map<std::string, int>> characteristics = { {1, { {"range", 2}, {"damage", 5}, {"fire rate", 1000}} },
                                                                  {2, { {"range", 3}, {"damage", 10}, {"fire rate", 700}} },
                                                                  {3, { {"range", 4}, {"damage", 15}, {"fire rate", 500}} } };

    void setUp() {
        setRange(characteristics[level]["range"]);
        setDamage(characteristics[level]["damage"]);
        fire_rate = characteristics[level]["fire rate"];
    }

public:

    explicit Tower(ElementType elementType);
    unsigned int getFireRate() const;
    void attack() override;

    void levelUp() override {
        if (level < 3) {
            level++;
            setUp();
        }
    }

    bool canBeLeveledUp() override {
        if (level == 3)
            return false;
        return true;
    }

    int getGold() const override {
        return 100;
    }

    ~Tower() override = default;

    TileType canBeBuilt() override;
};

