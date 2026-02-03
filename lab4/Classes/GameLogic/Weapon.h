#pragma once

#include "ElementType.h"
#include "GameObject.h"
#include "Enemy.h"
#include "TileType.h"

#include <memory>
#include <vector>


class Weapon: public GameObject {

    std::pair<unsigned int, unsigned int> position;

    /// Range of the weapon in Tiles.
    unsigned int range;

    /// Damage of the weapon.
    unsigned int damage;

    /// Type of tower: Hydro, Dendro, Cryo, Pyro or Electro.
    ElementType type;

    /// Current enemy in radius of weapon
    std::weak_ptr<Enemy> curr_focussed_enemy;

    unsigned int TILE_SIZE;

public:

    using Ptr = std::shared_ptr<Weapon>;

    explicit Weapon(ElementType elementType);

    bool hasLockOn();

    /// this function will be used
    /// to check if the enemy is still in range of weapon radius.
    /// if not, deselect the current focused enemy.
    void validateLockOn();

    Enemy::Ptr getLockOn();

    void lockOn(std::weak_ptr<Enemy> enemy);

    virtual void attack() {};

    bool isInRange(const Enemy::Ptr& enemy);

    unsigned int getRange() const;

    unsigned int getDamage() const;

    ElementType getElementType() const;

    void setRange(unsigned int range_var);

    void setDamage(unsigned int damage_var);

    virtual void levelUp() = 0;

    virtual ~Weapon() = default;

    virtual int getGold() const = 0;

    virtual TileType canBeBuilt() = 0;

    virtual bool canBeLeveledUp() = 0;

    void setPosition(float x, float y, unsigned int tile_size);
};

