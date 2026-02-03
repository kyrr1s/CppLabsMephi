#include "GUI_Element.h"

GUI_Element::GUI_Element(sf::Vector2f vector):vector(vector) {
}

void GUI_Element::setClickHandler(const GUI_Element::ClickHandler &handler) {
    click_handler = handler;
}

void GUI_Element::setHoverHandler(const GUI_Element::HoverHandler &handler) {
    hover_handler = handler;
}

void GUI_Element::click() {
    if (!click_handler) return;

    click_handler();
}

void GUI_Element::hover() {
    if (hover_handler) return;

    hover_handler();
}

float GUI_Element::getWidth() const {
    return vector.x;
}

float GUI_Element::getHeight() const {
    return vector.y;
}

void GUI_Element::setWidth(float width) {
    vector.x = width;
}

void GUI_Element::setHeight(float height) {
    vector.y = height;
}
