#pragma once

#include "EventStorage.h"
#include <SFML/Graphics/RenderWindow.hpp>

//!Adds or clears events from events storage.
class EventManager {

    /// Storage for events.
    EventStorage storage;

public:
    void clear();

    EventStorage *checkForEvents(sf::RenderWindow &window);
};

