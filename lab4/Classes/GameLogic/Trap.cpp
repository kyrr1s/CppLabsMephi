#include "Trap.h"
#include "TileType.h"

Trap::Trap(ElementType elementType):Weapon(elementType) {
    setDamage(75);
    setRange(1);
}

void Trap::attack() {
    //мб будет наносить урон всем врагам в радиусе?
    if(hasLockOn()) {
        getLockOn()->takeDamage(getDamage());
        getLockOn()->takeEffect(getElementType());
    }
}

TileType Trap::canBeBuilt() {
    return TileType::typePath;
}