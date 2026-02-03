#include "Path.h"

#include <iostream>

/**
 * @brief Hardcode for a path.
 * @param num - a number of a path.
 */

void Path::initialize(unsigned int num) {

    if (num == 0) {
        enemyPathingPoints.emplace_back(48, 80);
        enemyPathingPoints.emplace_back(48, 168);
        enemyPathingPoints.emplace_back(304, 168);
        enemyPathingPoints.emplace_back(304, 184);
        enemyPathingPoints.emplace_back(384, 184);
        enemyPathingPoints.emplace_back(384, 248);
        enemyPathingPoints.emplace_back(448, 248);
        enemyPathingPoints.emplace_back(448, 296);
    }

    if (num == 1) {
        enemyPathingPoints.emplace_back(304, 64);
        enemyPathingPoints.emplace_back(304, 184);
        enemyPathingPoints.emplace_back(384, 184);
        enemyPathingPoints.emplace_back(384, 248);
        enemyPathingPoints.emplace_back(448, 248);
        enemyPathingPoints.emplace_back(448, 296);
    }

}

/**
 * @return Enemy spawn point.
 */

sf::Vector2<int> Path::getEnemySpawnTileCoordinate() const {
    if (enemyPathingPoints.empty()) {
        throw std::logic_error("No enemy spawn point set");
    }

    return *enemyPathingPoints.begin();
}

/**
 * @return Enemy final point.
 */

sf::Vector2<int> Path::getEnemyTargetTileCoordinate() const {
    if (enemyPathingPoints.empty()) {
        throw std::logic_error("No enemy target point set");
    }

    return *enemyPathingPoints.end();
}

/**
 * @param pathIndex - a number of a point on a path.
 * @return Enemy's next point.
 */

sf::Vector2<int> Path::getEnemyPathTileCoordinate(unsigned int pathIndex) const {

    if(pathIndex >= enemyPathingPoints.size()) {
        return enemyPathingPoints[enemyPathingPoints.size() - 1];
    }

    return enemyPathingPoints[pathIndex];
}

/**
 * @brief Sets a direction for an enemy.
 * @param currentPosition - current position of an enemy.
 * @param targetPosition - current target position for an enemy.
 */

Direction Path::determineDirection(sf::Vector2<float> currentPosition, sf::Vector2<float> targetPosition) const {
    std::cout << targetPosition.x << " " << targetPosition.y << " and ";
    std::cout << currentPosition.x << " " << currentPosition.y;
    float leftOverX = targetPosition.x - currentPosition.x;
    float leftOverY = targetPosition.y - currentPosition.y;

    if (leftOverX > 0.f) {
        std::cout << " east" << std::endl;
        return Direction::East;
    }

    if (leftOverX < 0.f) {
        std::cout << " west" << std::endl;
        return Direction::West;
    }

    if (leftOverY < 0.f) {
        std::cout << " north" << std::endl;
        return Direction::North;
    }

    std::cout << " south" << std::endl;
    return Direction::South;
}