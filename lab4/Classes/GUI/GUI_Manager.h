#pragma once

#include "GUI_Element.h"

#include <vector>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>

class GUI_Manager {

    /// Storage for GUI elements
    std::vector<GUI_Element *> gui_elements;

public:

    /// Adds a GUI element to the end of gui_elements vector
    void push_back(GUI_Element *element);

    /// Checks if there is an element on that position. If there is an element, clicks on it, does nothing otherwise
    void checkClick(sf::Vector2i position);
};