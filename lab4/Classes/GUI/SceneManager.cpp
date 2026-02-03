#include "SceneManager.h"
#include <iostream>
#include <windows.h>

void SceneManager::update(EventStorage *events) {

    if (current_scene == nullptr) {
        MessageBox(nullptr, "There is no scene to be updated!", "Error!", MB_OK);
        return;
    }

    current_scene->update(game, events);
}

void SceneManager::draw(sf::RenderWindow &window) const {

    if (current_scene == nullptr) {
        MessageBox(nullptr, "There is no scene to be drawn!", "Error!", MB_OK);
        return;
    }

    current_scene->draw(window);
}

void SceneManager::fixedUpdate(EventStorage *events) {

    if (current_scene == nullptr) {
        MessageBox(nullptr, "There is no any scene to be fixed updated!", "Error!", MB_OK);
        return;
    }

    current_scene->fixedUpdate(game, events);
}

void SceneManager::setGameInstance(Game *game_var) {
    game = game_var;
}