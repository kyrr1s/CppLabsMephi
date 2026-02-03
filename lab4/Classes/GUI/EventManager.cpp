#include "EventManager.h"
#include <SFML/Window/Event.hpp>

/**
 * @brief Checks for new events from param, is being called once a frame.
 * @param window - An object via new events are collected.
 * @return An updated storage with new events.
 */
EventStorage *EventManager::checkForEvents(sf::RenderWindow &window) {
    sf::Event currentEvent{};

    // Pop the event on top of the event queue, if any, and return it;
    // False if queue is empty
    while (window.pollEvent(currentEvent))
        storage.add(currentEvent.type, currentEvent);

    // We need to return a reference just because EventStorage is a big object
    return &storage;
}

/**
 * @brief Clears all previous events from the bag, should be used before all other methods
 */
void EventManager::clear() {
    storage.clear();
}