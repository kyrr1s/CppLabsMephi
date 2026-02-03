#include "MenuOption.h"

#include <utility>

MenuOption::MenuOption(sf::Text text_var, float width, float height) : GUI_Element({width, height}), disabled(false),
                                                           text(std::move(text_var)) {
    rectangle = sf::RectangleShape({width, height});

    text.setPosition((width - text.getGlobalBounds().width) / 2,
                       (height - text.getGlobalBounds().height) / 2 - 5);
}

void MenuOption::setDisabled(const bool &disabled_var) {
    disabled = disabled_var;
    rectangle.setFillColor(disabled ? sf::Color{122, 122, 122} : color);
}

bool MenuOption::isDisabled() const {
    return disabled;
}

void MenuOption::click() {
    if (!disabled) {
        GUI_Element::click();
    }
}

void MenuOption::hover() {
    if (!disabled) {
        GUI_Element::hover();
    }
}

void MenuOption::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    //The 3x3 matrix (sf::Transform - its wrapper) stores the position, orientation and scaling of the object.
    //Multiplying two matrices will give a new matrix, the dominant position/orientation/scaling of the first two
    //This is used for positioning child objects relative to the parent.
    states.transform *= getTransform();

    target.draw(rectangle, states);
    target.draw(text, states);
}

void MenuOption::setText(const char *new_text) {
    text.setString(new_text);
}

void MenuOption::setColor(const sf::Color &bg_color) {
    rectangle.setFillColor(bg_color);
    color = bg_color;
}

void MenuOption::setTextColor(const sf::Color &text_color) {
    text.setFillColor(text_color);
}

void MenuOption::setCharacterSize(const size_t &size) {
    text.setCharacterSize(size);
}