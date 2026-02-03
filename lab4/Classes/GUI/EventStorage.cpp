#include "EventStorage.h"

/**
 * @brief Adds an event to the storage.
 * @param eventType - type of a newEvent.
 * @param newEvent - new event of SFML Event class.
 */

void EventStorage::add(sf::Event::EventType eventType, sf::Event newEvent) {
    events_map[eventType] = newEvent;
}

/**
 * @brief Checks if an event of special type is already in storage.
 * @param eventType - type of an event which we are looking for.
 * @return True, if storage has an event with that type; False, otherwise.
 */

bool EventStorage::inStock(sf::Event::EventType eventType) {
    // A place of that event, equals map's end,
    // If there is no that type of event in storage
    auto it = events_map.find(eventType);

    return it != events_map.end();
}

/**
 * @brief Gets an event of special type that may have happened on this frame.
 * @param eventType - type of an event which we are looking for.
 * @return An event of that type in storage.
 */

sf::Event *EventStorage::at(sf::Event::EventType eventType) {
    return &events_map[eventType];
}

/**
 * @brief Clears the storage. is being called once a frame.
 */

void EventStorage::clear() {
    events_map.clear();
}

/**
 * @brief Gets an event of special type and erase it from storage.
 * @param eventType - type of an event which we are looking for.
 * @return An event of that type in storage.
 */

sf::Event *EventStorage::pop(sf::Event::EventType eventType) {
    auto event = at(eventType);
    events_map.erase(eventType);

    return event;
}