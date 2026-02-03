#include "WeaponGUI.h"

#include <utility>

WeaponGUI::WeaponGUI(ElementType elementType, float tile_size) :
    selected(false), is_built(false) {
    TILE_SIZE = tile_size;
    radius_shape.setFillColor(sf::Color{235, 79, 52, 20});
    radius_shape.setOutlineThickness(2);
    radius_shape.setOutlineColor(sf::Color(235, 79, 52, 128));
}

void WeaponGUI::draw(sf::RenderTarget &target, sf::RenderStates states) {
    //states.transform *= getTransform();
    if (weapon->getRange() != -1) {//it does not exist
        //if (selected || !is_built)
            target.draw(radius_shape, states);

        target.draw(sprite, states);
    }
}

void WeaponGUI::setTexture(const sf::Texture &texture, sf::Rect<int> textureCoords) {
    sprite.setTexture(texture);
    sprite.setTextureRect(textureCoords);
}

const sf::Sprite& WeaponGUI::getSprite() const {
    return sprite;
}

sf::Sprite& WeaponGUI::getSprite() {
    return sprite;
}

void WeaponGUI::setSelected(bool selected_var) {
    selected = selected_var;
    weapon->setPosition(sprite.getPosition().x+TILE_SIZE/2, sprite.getPosition().y+TILE_SIZE/2, TILE_SIZE);
    radius_shape.setPosition(sprite.getPosition().x+TILE_SIZE/2, sprite.getPosition().y+TILE_SIZE/2);
    radius_shape.setRadius(static_cast<float>(weapon->getRange() * TILE_SIZE));
    radius_shape.setOrigin(radius_shape.getRadius(), radius_shape.getRadius());
}

void WeaponGUI::changeRadius() {
    radius_shape.setRadius(static_cast<float>(weapon->getRange() * TILE_SIZE));
    radius_shape.setOrigin(radius_shape.getRadius(), radius_shape.getRadius());
}

void WeaponGUI::build() {
    is_built = true;
}

bool WeaponGUI::isBuilt() const {
    return is_built;
}

Weapon::Ptr WeaponGUI::getWeapon() const {
    return weapon;
}

void WeaponGUI::setWeapon(Weapon::Ptr weapon_var) {
    weapon = std::move(weapon_var);
}

TileType WeaponGUI::isBuildable() {
    return weapon->canBeBuilt();
}