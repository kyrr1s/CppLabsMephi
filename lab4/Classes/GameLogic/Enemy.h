#pragma once
#define HEALTH_BAR_LENGTH 35
#define HEALTH_BAR_HEIGHT 2

#include "GameObject.h"
#include "Direction.h"
#include "ElementType.h"

#include <memory>
#include <functional>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <SFML/System/Vector2.hpp>

//! Enemy of a game.
class Enemy : public GameObject, public std::enable_shared_from_this<Enemy> {

public:
    using Ptr = std::shared_ptr<Enemy>;
    using EnemyGoalHandler = std::function<void(const Enemy::Ptr&)>;
    using EnemyDeadHandler = std::function<void(const Enemy::Ptr&)>;

private:

    /// Sprite of the enemy. Texture being provided by parent class
    sf::Sprite sprite;

    /// Healthbars
    sf::RectangleShape back_ground_healthbar;
    sf::RectangleShape fore_ground_healthbar;

    /// Health of enemy.
    unsigned int health;

    /// The amount of health the enemy used to have an aupdate ago.
    unsigned initial_health;

    /// Progress of the enemy in the map. Could be anything.
    /// Higher the progress, more chance of being focused by a tower.
    unsigned int progress_value;

    /// The current path this enemy is on.
    unsigned int pathing_index;

    unsigned int gold_worth;

    /// Callback when enemy reaches end of path.
    EnemyGoalHandler goal_handler;

    /// Callback when enemy gets killed by a weapon.
    EnemyDeadHandler enemy_dead_handler;

    /// Name of an enemy, required to set a sprite.
    std::string name;

    /// Name of a reaction.
    sf::Text effect_name;

    /// The amounts of X and Y this enemy has to move each update.
    float moveX;
    float moveY;

    /// Speed of the enemy. Equals to 0.5f initially.
    float speed = 0.5f;

    /// The amount of distance this enemy needs to cover.
    /// Until it needs to request a new direction.
    float distance;

    /// Callback when enemy reaches end of the path.
    EnemyGoalHandler goalHandler;

    /// Callback when enemy gets killed by a weapon.
    EnemyDeadHandler enemyDeadHandler;

    /// Current element effect.
    ElementType current_effect = None;

    /// Helpful for reactions.
    unsigned int critical_damage = 1;
    unsigned int weakness = 1;

    /// Element duration. The same for all elements.
    unsigned int element_duration = 5000;

    /// Time when there was last element tick.
    sf::Clock last_element_tick;

    /// Effect power. Equals to 1 initially.
    unsigned int effect_power = 1;

public:

    void setCrit(unsigned int var) { critical_damage = var; }

    void setWeakness(unsigned int var) { weakness = var; }

    explicit Enemy(unsigned int health, std::string  name_var, unsigned int goldWorth = 10);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void setGoalHandler(EnemyGoalHandler handler);

    void setEnemyDeadHandler(EnemyDeadHandler handler);

    void kill();

    void step();

    void reachGoal();

    void setTexture(const sf::Texture &texture, const sf::Rect<int> &texCoords);

    bool needsNewPath() const;

    void takeDamage(unsigned int damage);

    unsigned int getGoldWorth() const;

    unsigned int getProgress() const;

    unsigned int getHealth() const;

    unsigned int getPathingIndex() const;

    void setDirection(Direction direction, sf::Vector2<float> targetPosition);

    void takeEffect(ElementType type);

    void tickEffect();
};

