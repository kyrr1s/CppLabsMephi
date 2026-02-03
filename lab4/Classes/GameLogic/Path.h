#pragma once

#include "Tile.h"
#include "Direction.h"

#include <array>
#include <vector>
#include <cmath>
#include <unordered_map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

//! Path for enemies.
class Path : public sf::Drawable, public sf::Transformable {

    std::vector<Tile> tiles;

    std::vector<sf::Vector2<int>> enemyPathingPoints;

public:
    Path() = default;

    void initialize(unsigned int num);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {}

    sf::Vector2<int> getEnemySpawnTileCoordinate() const;

    sf::Vector2<int> getEnemyTargetTileCoordinate() const;

    sf::Vector2<int> getEnemyPathTileCoordinate(unsigned int pathIndex) const;

    Direction determineDirection(sf::Vector2<float> currentPosition, sf::Vector2<float> targetPosition) const;

};

