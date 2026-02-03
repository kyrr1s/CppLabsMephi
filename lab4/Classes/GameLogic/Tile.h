#pragma once

#include "TileType.h"
#include "Weapon.h"

#include <memory>

//! A grind of a map. All weapons and enemies are located on tiles.
class Tile {

    /// Type of that tile.
    TileType tile_type;

    ///Weapon on that tile.
    std::weak_ptr<Weapon> weapon;

    ///X position of a tile.
    float x_position{};

    ///Y position of a tile.
    float y_position{};

public:

    ///A size of a tile.
    float TILE_SIZE;

    using Ptr = std::shared_ptr<Tile>;

    Tile() = default;

    explicit Tile(TileType type, float x, float y, float tile_size);

    TileType getType() const;

    [[nodiscard]] bool isBuildable() const;

    [[nodiscard]] bool hasWeapon() const;

    void setWeapon(std::weak_ptr<Weapon> weapon);

    Weapon::Ptr getWeapon();

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;
};


