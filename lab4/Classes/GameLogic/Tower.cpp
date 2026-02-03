#include "Tower.h"
#include "TileType.h"

Tower::Tower(ElementType elementType): Weapon(elementType) {
    setUp();
}

unsigned int Tower::getFireRate() const {
    return fire_rate;
}

/**
 * @brief Attack an enemy that is curr. focused on.
 */

void Tower::attack() {
    if(hasLockOn())
        if(timeof_last_shot.getElapsedTime().asMilliseconds() >= getFireRate()) {
            getLockOn()->takeDamage(getDamage());
            getLockOn()->takeEffect(getElementType());
            timeof_last_shot.restart();
        }
}

/**
 * @return A type of a tile where tower can be bield on.
 */

TileType Tower::canBeBuilt() {
    return TileType::typeField;
}

