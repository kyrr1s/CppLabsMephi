#include "WeaponManager.h"
#include <iostream>

void WeaponManager::push(const Weapon::Ptr &weapon) {
    weapons.push_back(weapon);
}

void WeaponManager::pop(const Weapon::Ptr &weapon) {
    weapons.erase(std::find(weapons.begin(), weapons.end(), weapon));
}

void WeaponManager::handleEnemyLockOn(EnemyManager *enemyManager) {
    for (const auto& weapon : weapons) {
        if (weapon->hasLockOn()) {
            weapon->validateLockOn();
            continue;
        }
        enemyManager->tryGetLockOn(weapon);
    }
}

void WeaponManager::update() {
    for (const auto &weapon : weapons)
        if(weapon!=nullptr && weapon->hasLockOn()) {
            weapon->attack();
            if (weapon->canBeBuilt() == TileType::typePath) { //Trap case
                weapon->setRange(-1);
                pop(weapon);
            }

        }
}
