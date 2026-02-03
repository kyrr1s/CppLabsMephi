#pragma once

#include "../GameLogic/Weapon.h"
#include "TileGUI.h"
#include "MapObject.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Transformable.hpp>

class WeaponGUI: public MapObject {

    bool is_built;

    /// Sprite of the tower.
    sf::Sprite sprite;

    /// Since tower is selected, its radius will be rendered.
    sf::CircleShape radius_shape;

    /// Checks weapon is selected or not.
    bool selected;

    std::shared_ptr<Weapon> weapon;

public:

    float TILE_SIZE;

    using Ptr = std::shared_ptr<WeaponGUI>;

    WeaponGUI(ElementType elementType, float tile_size);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void setTexture(const sf::Texture &texture, sf::Rect<int> textureCoords);
    void setSelected(bool selected_var);
    void build();
    bool isBuilt() const;
    Weapon::Ptr getWeapon() const;

    const sf::Sprite& getSprite() const;
    sf::Sprite& getSprite();

    void setWeapon(Weapon::Ptr weapon_var);

    void changeRadius();

    TileType isBuildable();

    void draw(sf::RenderTarget &target, sf::RenderStates states);
};