#include "MapObject.h"

#include <SFML/Graphics/Rect.hpp>

float parseFloat(const std::string &str) {
    char *pEnd = nullptr;
    const float value = strtof(str.c_str(), &pEnd);
    if (*pEnd != '\0')
        throw std::runtime_error("'" + str + "' is not a float number");
    return value;
}

int MapObject::getPropertyInt(const std::string &propertyName) {
    return std::stoi(properties[propertyName]);
}

float MapObject::getPropertyFloat(const std::string &propertyName) {
    return parseFloat(properties[propertyName]);
}

std::string MapObject::getPropertyString(const std::string &propertyName) {
    return properties[propertyName];
}

//sf::Rect<float> MapObject::getRect() const {
//    return rect;
//}