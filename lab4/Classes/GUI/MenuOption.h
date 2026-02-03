#pragma once
#include "GUI_Element.h"

#include <string>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class MenuOption : public GUI_Element, public sf::Drawable  {

    /// Shows whether UIElement cause events or not. If true, it does not, it does otherwise.
    bool disabled = false;

    /// Text in a button's body.
    sf::Text text;

    /// A rectangle, associated with a button.
    sf::RectangleShape rectangle;

    ///The fill color of the shape.
    sf::Color color;

public:

    MenuOption() = default;

    /// Sets button's text, color and shape.
    explicit MenuOption(sf::Text text, float width = 100, float height = 20);

    /// Renders a button.
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    /// Checks button status.
    bool isDisabled() const;

    /// Sets button status.
    void setDisabled(const bool &disabled);

    /// Sets text in a button's body.
    void setText(const char *text);

    /// Sets a color of a text in a button's body.
    void setTextColor(const sf::Color &color);

    /// Sets the fill color of the shape.
    void setColor(const sf::Color &color);

    /// Sets character size of a text in a button's body.
    void setCharacterSize(const size_t &size);

    /// Triggers a click function of a button, that is not disabled.
    void click() override;

    /// Triggers a hover function of a button, that is not disabled.
    void hover() override;

};
