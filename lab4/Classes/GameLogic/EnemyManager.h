#pragma once

#include "Enemy.h"
#include "Path.h"
#include "Tower.h"

#include <vector>
#include <algorithm>
#include <unordered_map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

//! Manager for enemies pathing.
class EnemyManager {

    void cleanUp();

    /// Vector of enemies that have not stepped.
    std::vector<Enemy::Ptr> enemies;

    /// Vector of enemies that have already stepped.
    std::vector<Enemy::Ptr> enemies_after_step;

    /// Enemy texture coordinates.
    std::unordered_map<std::string, sf::Rect<int>> enemy_textures_coords;

    /// Enemy tileset.
    sf::Texture enemy_tileset;

public:

    EnemyManager();

    void update();

    void removeEnemy(const Enemy::Ptr &enemy);

    void addEnemy(const Enemy::Ptr &enemy);

    std::size_t getEnemyCount();

    void handleEnemyPathing(const Path& path);

    void tryGetLockOn(const Weapon::Ptr& weapon);

    void draw(sf::RenderTarget& target) const;
};
