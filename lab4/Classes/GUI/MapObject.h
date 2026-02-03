#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>

class MapObject {

public:

    std::string name;

    std::string type;

    sf::Rect<float> rect;

    std::map<std::string, std::string> properties;

    sf::Sprite sprite;

    int getPropertyInt(const std::string &propertyName);

    float getPropertyFloat(const std::string &propertyName);

    std::string getPropertyString(const std::string &propertyName);

//    void moveBy(const sf::Vector2f &movement);
//
//    void moveTo(const sf::Vector2f &position);
//
//    sf::Rect<float> getRect() const;
//
//    bool collidesWith(MapObject *gameObject);
};

float parseFloat(const std::string &str);