#pragma once

#include <SFML/Graphics.hpp>

class GameObject: public sf::Transformable, public sf::Drawable {

    /// Width of an object.
    float width;

    /// Height of an object.
    float height;

public:

    GameObject() = default;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

    bool collidesWith(GameObject * other);

    void setHeight(float height);

    void setWidth(float width);

    float getHeight() const;

    float getWidth() const;

};

