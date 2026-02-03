#include "Tile.h"

#include <utility>

Tile::Tile(TileType type, float x, float y, float tile_size) :
    tile_type(type), x_position(x), y_position(y), TILE_SIZE(tile_size) {}

TileType Tile::getType() const {
    return tile_type;
}

bool Tile::isBuildable() const {
    return tile_type == typePath || tile_type == typeField;
}

bool Tile::hasWeapon() const {
    return !weapon.expired();
}

void Tile::setWeapon(std::weak_ptr<Weapon> weapon_var) {
    weapon = std::move(weapon_var);
}

float Tile::getX() const {
    return x_position;
}

float Tile::getY() const {
    return y_position;
}

Weapon::Ptr Tile::getWeapon() {
    return weapon.lock();
}