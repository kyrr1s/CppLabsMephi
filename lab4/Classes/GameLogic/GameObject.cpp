#include "GameObject.h"

/**
 * @brief Checks if two objects collide or not.
 */

bool GameObject::collidesWith(GameObject *gameObject) {
    sf::Rect<float> currentRect(getPosition(), {
            width,
            height
    });

    sf::Rect<float> targetRect(gameObject->getPosition(), {
            gameObject->getWidth(),
            gameObject->getHeight()
    });

    return currentRect.intersects(targetRect);
}

/**
 * @brief Sets object's height.
 */

void GameObject::setHeight(float height_v) {
    height = height_v;
}

/**
 * @brief Sets object's width.
 */

void GameObject::setWidth(float width_v) {
    width = width_v;
}

/**
 * @return Object's height.
 */

float GameObject::getHeight() const {
    return height;
}

/**
 * @return  Object's width.
 */

float GameObject::getWidth() const {
    return width;
}