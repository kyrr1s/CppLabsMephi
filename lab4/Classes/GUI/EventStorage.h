#pragma once

#include <SFML/Window/Event.hpp>
#include <unordered_map>

//! Manager for events.
class EventStorage {

    /// Hash-table for events with its type, we need to save elements order
    std::unordered_map<sf::Event::EventType, sf::Event> events_map;

public:
    void add(sf::Event::EventType eventType, sf::Event newEvent);

    bool inStock(sf::Event::EventType eventType);

    sf::Event *at(sf::Event::EventType eventType);

    void clear();

    sf::Event *pop(sf::Event::EventType eventType);
};
