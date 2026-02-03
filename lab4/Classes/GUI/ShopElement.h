#pragma once

#include "GUI_Element.h"
#include "WeaponGUI.h"

#include <memory>
#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/// An element of a in-game shop.
class ShopElement: public GUI_Element, public sf::Drawable {

    /// Name of a tower to buy.
    sf::Text weapon_name;

    /// Price of a tower or trap.
    sf::Text gold_text;

    /// Type of tower or trap.
    ElementType weapon_type;

    /// Tower texture.
    sf::RectangleShape background;

public:

    ShopElement() = default;

    /// Sets that shop element characteristics to render.
    ShopElement(ElementType weaponType, sf::Text weaponText, sf::Text goldText);

    /// Draws that shop element
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /// Gets that shop element

    std::shared_ptr<WeaponGUI> getTower(float tile_size) const;

    std::shared_ptr<WeaponGUI> getTrap(float tile_size) const;

    void setColor(sf::Color color);
};