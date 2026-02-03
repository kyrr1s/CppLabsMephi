#include "GUI_Manager.h"

#include <iostream>

void GUI_Manager::push_back(GUI_Element *element) {
    gui_elements.push_back(element);
}

void GUI_Manager::checkClick(sf::Vector2i position) {

    // Checks if window is open
    if (position.x == 0 && position.y == 0) return; // window::isOpen does not work?

    // If the elements are superimposed on each other, we should click on the one at the top
    // Therefore we should use reverse iterator

    //todo: can I make it more effective? O(1)?
    //todo: why range-based loop in not working?
    for (auto it = gui_elements.rbegin(); it != gui_elements.rend(); it++) {

        // Current gui element
        GUI_Element *element = *it;

        // A current element's position on a window
        const float x = element->getPosition().x;
        const float y = element->getPosition().y;

        // Characteristics of a current element, width (x-axis) and height (reversed y-axis)
        const float width = element->getWidth();
        const float height = element->getHeight();

        // Checks if all params are not in controversial and chooses the right element
        if (position.x >= x && position.x <= x + width &&
            position.y >= y && position.y <= y + height)
                // OK, let's click on that element
                return element->click();
    }
}