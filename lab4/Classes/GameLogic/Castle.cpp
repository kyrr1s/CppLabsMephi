#include "Castle.h"

/**
 * @brief Adds health to a castle.
 * @param health_var - an amount of health to be added.
 */

void Castle::addHealth(unsigned int health_var) {
    health += health_var;
}

/**
 * @brief Substracts health.
 * @param health_var - an amount of health to be substracted.
 */

void Castle::substractHealth(unsigned int health_var) {
    if (health_var > health) {
        health = 0;
        return;
    }

    health -= health_var;
}

/**
 * @brief Sets health.
 * @param health_var - an amount of health to be setted.
 */

void Castle::setHealth(unsigned int health_var) {
    health = health_var;
}

/**
 * @return Health of a castle.
 */

unsigned int Castle::getHealth() const {
    return health;
}