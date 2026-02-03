#include "Enemy.h"

#include <cmath>
#include <utility>

/**
 * @brief Sets enemy's health, name and sprite.
 * @param health - an amount of health to be setted.
 * @param name_var - a name of an enemy.
 * @param goldWorth - an amount of gold that player gets after killing an enemy.
 */

Enemy::Enemy(unsigned int health, std::string name_var, unsigned int goldWorth)
        : GameObject(), health(health), name(std::move(name_var)), gold_worth(goldWorth), progress_value(0),
          pathing_index(0), moveX(0.f), moveY(0.f), distance(0.f) {
    initial_health = health;

    fore_ground_healthbar.setFillColor(sf::Color::Green);
    back_ground_healthbar.setFillColor(sf::Color::Red);

    fore_ground_healthbar.setSize({HEALTH_BAR_LENGTH, HEALTH_BAR_HEIGHT});
    back_ground_healthbar.setSize({HEALTH_BAR_LENGTH, HEALTH_BAR_HEIGHT});

    fore_ground_healthbar.setPosition(-HEALTH_BAR_LENGTH / 2.f, -20.f);
    back_ground_healthbar.setPosition(-HEALTH_BAR_LENGTH / 2.f, -20.f);
}

/**
 * @brief Draws an enemy.
 * @param target - an object that draws.
 * @param states - states for drawing with SFML.
 */

void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(sprite, states);

    if (initial_health > health) {
        target.draw(back_ground_healthbar, states);
        target.draw(fore_ground_healthbar, states);
        target.draw(effect_name, states);
    }
}

/**
 * @brief Substracts health from an enemy.
 * @param damage - an amount that be substracted from enemy's health.
 */

void Enemy::takeDamage(unsigned int damage) {
    if (damage*critical_damage*weakness >= health) {
        health = 0;
        return kill();
    }

    health -= damage*critical_damage*weakness;
    critical_damage = 1;

    const float healthPercentage = 100.f / static_cast<float>(initial_health) * static_cast<float>(health);
    fore_ground_healthbar.setSize(
            {HEALTH_BAR_LENGTH / 100.f * healthPercentage, HEALTH_BAR_HEIGHT});
}

#include <iostream>

/**
 * @brief Sets effect on an enemy.
 * @param type - an element type to be setted.
 */

void Enemy::takeEffect(ElementType type) {
    if (current_effect == None) {
        current_effect = type;
        last_element_tick.restart();
    }
    else {
        if (current_effect == Pyro) {
            if (type == Hydro) {
                //can make some logic here
            }

            if (type == Electro) {
                current_effect = Overloading;
            }

            if (type == Cryo) {
                current_effect = Melting2x;
            }

            if (type == Dendro) {
                current_effect = Burning;
            }
            last_element_tick.restart();
        }

        if (current_effect == Hydro) {
            if (type == Pyro) {
                current_effect = Steam;
            }

            if (type == Electro) {
                current_effect = Charge;
            }

            if (type == Cryo) {
                current_effect = Slowing;
            }

            if (type == Dendro) {
                current_effect = Blossom;
            }
            last_element_tick.restart();
        }

        if (current_effect == Electro) {
            if (type == Pyro) {
                current_effect = Overloading;
            }

            if (type == Hydro) {
                current_effect = Charge;
            }

            if (type == Cryo) {
                current_effect = Weakening;
            }

            if (type == Dendro) {
                // can make some logic here
            }
            last_element_tick.restart();
        }

        if (current_effect == Cryo) {
            if (type == Pyro) {
                current_effect = Melting1and5x;
            }

            if (type == Hydro) {
                current_effect = Slowing;
            }

            if (type == Electro) {
                current_effect = Weakening;
            }

            if (type == Dendro) {
                // can make some logic here
            }
            last_element_tick.restart();
        }

        if (current_effect == Dendro) {
            if (type == Pyro) {
                // can make some logic here
            }

            if (type == Hydro) {
                current_effect = Blossom;
            }

            if (type == Electro) {
                current_effect = Stimulation;
            }

            if (type == Cryo) {
                current_effect = Split;
            }
            last_element_tick.restart();
        }
        //last_element_tick.restart();
    }
    if (current_effect == None || current_effect == Overloading ||
        current_effect == Melting2x || current_effect == Melting1and5x ||
        current_effect == Burning || current_effect == Steam ||
        current_effect == Charge || current_effect == Slowing ||
        current_effect == Stimulation || current_effect == Blossom ||
        current_effect == Weakening || current_effect == Split) {
        sprite.setColor(sf::Color::White);
    }
    if (current_effect == Pyro) {
        sprite.setColor(sf::Color{255,0,0,200});
    }
    if (current_effect == Hydro) {
        sprite.setColor(sf::Color{0,0,255,200});
    }
    if (current_effect == Electro) {
        sprite.setColor(sf::Color{128,0,125,200});
    }
    if (current_effect == Cryo) {
        sprite.setColor(sf::Color{117, 187, 253, 200});
    }
    if (current_effect == Dendro) {
        sprite.setColor(sf::Color{0, 255, 0, 200});
    }
}

/**
 * @brief Does the element reaction and changes an element.
 */

void Enemy::tickEffect() {
   if (current_effect == None)// || current_effect == Pyro || current_effect == Hydro ||
//        current_effect == Cryo || current_effect == Electro || current_effect == Dendro)
        return;
    if(last_element_tick.getElapsedTime().asMilliseconds() <= element_duration) {

        if (current_effect == Overloading) {
            std::cout << "overloading!" << std::endl;
            moveX = 0;
            moveY = 0;
        }
        if (current_effect == Melting2x) {
            std::cout << "melting2x!" << std::endl;
            critical_damage = 2*effect_power;
            current_effect = None;
        }
        if (current_effect == Burning) {
            std::cout << "burning!" << std::endl;
            takeDamage(effect_power*10);
        }
        if (current_effect == Steam) {
            std::cout << "steam!" << std::endl;
            //враг путается и может выйти с карты
            if (moveX == 0.f && moveY == -speed) { //North case
                move(0, speed*2*effect_power);
                sprite.setRotation(0);
            }
            if (moveX == speed && moveY == 0.f) { //East case
                move(-speed*2*effect_power,0);
                sprite.setRotation(90);
            }
            if (moveX == 0.f && moveY == speed) { //South case
                move(0,-speed*2*effect_power);
                sprite.setRotation(180);
            }
            if (moveX == -speed && moveY == 0.f) { //West case
                move(speed*2*effect_power,0);
                sprite.setRotation(270);
            }
            if (moveX == 0 && moveY == 0) {
                kill();
            }
        }
        if (current_effect == Charge) {
            std::cout << "charge!" << std::endl;
            //???
        }
        if (current_effect == Slowing) {
            std::cout << "slowing!" << std::endl;
            speed /= 2*effect_power;
            current_effect = Canselled;
        }
        if (current_effect == Blossom) {
            std::cout << "blossom!" << std::endl;
            //???
        }
        if (current_effect == Weakening) {
            std::cout << "weakening!" << std::endl;
            weakness = 2*effect_power;
            current_effect = Canselled;
        }
        if (current_effect == Melting1and5x) {
            std::cout << "melting1and5x!" << std::endl;
            critical_damage = 1.5*effect_power;
            current_effect = None;
        }
        if (current_effect == Stimulation) {
            std::cout << "stimulation!" << std::endl;
            effect_power = 2;
            current_effect = Canselled;
        }
        if (current_effect == Split) {
            std::cout << "split!" << std::endl;
            critical_damage = 2*effect_power;
            current_effect = None;
        }
    }
    else {
        current_effect = None;
        sprite.setColor(sf::Color::White);
        speed = 0.5f;
        weakness = 1;
    }
}

/**
 * @return Health of an enemy.
 */

unsigned int Enemy::getHealth() const {
    return health;
}

/**
 * @return Progress of enemy pathing.
 */

unsigned int Enemy::getProgress() const {
    return progress_value;
}

/**
 * @brief Sets texture.
 * @param texture - a SFML texture to set.
 * @param texCoords - a SFML coordinated of a rectangle with textures.
 */

void Enemy::setTexture(const sf::Texture &texture, const sf::Rect<int> &texCoords) {
    sprite.setTexture(texture);
    sprite.setTextureRect(texCoords);

    // Set the origin to the center of the sprite
    // Since that's more convenient for us.
    sprite.setOrigin(texCoords.width / 2.f, texCoords.height / 2.f);
}

/**
 * @brief Stops an enemy.
*/

void Enemy::step() {
    if (distance <= 0) {
        return;
    }

    if(distance >= std::abs(moveY + moveX))
        distance -= std::abs(moveY + moveX);
    else distance = 0;

    move(moveX, moveY);
}

/**
  * @return Pathing index of an enemy.
 */

unsigned int Enemy::getPathingIndex() const {
    return pathing_index;
}

/**
 * @brief Sets direction.
 * @param direction - en enum type of direction.
 */

void Enemy::setDirection(Direction direction, sf::Vector2<float> targetPosition) {
    pathing_index++;

    float leftOverX = targetPosition.x - getPosition().x;
    float leftOverY = targetPosition.y - getPosition().y;

    distance = std::abs(leftOverX + leftOverY);

    if (direction == Direction::North) {
        moveX = 0.f;
        moveY = -speed;

        sprite.setRotation(180);

        return;
    }

    if (direction == Direction::East) {
        moveX = speed;
        moveY = 0.f;

        sprite.setRotation(270);

        return;
    }

    if (direction == Direction::South) {
        moveX = 0.f;
        moveY = speed;

        sprite.setRotation(0);

        return;
    }

    if (direction == Direction::West) {
        moveX = -speed;
        moveY = 0.f;

        sprite.setRotation(90);
    }
}

/**
 * @brief Checks if enemy needs a new path or not.
 * @return True, if distance <= 0, False, otherwise.
 */

bool Enemy::needsNewPath() const {
    return distance <= 0.f;
}

/**
 * @brief Sets a function that triggers when enemy reaches a distination.
 */

void Enemy::setGoalHandler(Enemy::EnemyGoalHandler handler) {
    goal_handler = std::move(handler);
}

/**
 * @brief Trigger a goal handler.
 */

void Enemy::reachGoal() {
    goal_handler(shared_from_this());
}

/**
 * @brief Sets a function that triggers when enemy dies.
 */

void Enemy::setEnemyDeadHandler(Enemy::EnemyDeadHandler handler) {
    enemy_dead_handler = std::move(handler);
}

/**
 * @brief Kills an enemy.
*/

void Enemy::kill() {
    enemy_dead_handler(shared_from_this());
}

/**
 * @return Gold that player gets after killing that enemy.
 */

unsigned int Enemy::getGoldWorth() const {
    return gold_worth;
}