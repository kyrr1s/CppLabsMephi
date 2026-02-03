#pragma once
#include "Scene.h"
#include "EventStorage.h"
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

class Game;

class SceneManager {

    /// Current scene to be drawn and updated in main loop of a game.
    std::unique_ptr<Scene> current_scene;

    /// An instance of the Game object, that draws and updates a current scene.
    Game *game;

public:

    template<class SceneClass, class ...Args>
    void setScene(Args... args) {

        // Checks if there is another running screen
        if (current_scene != nullptr) {
            current_scene->leave(game);
        }

        // Reset a current scene
        current_scene.reset();
        current_scene = std::make_unique<SceneClass>(args...);

        // Sets up GUI of a scene
        current_scene->setGUI(game);

        //
        current_scene->enter(game);
    }

    /// Fixed updates a current screen.
    void fixedUpdate(EventStorage *events);

    /// Updates a current screen.
    void update(EventStorage *event);

    /// Draws a current screen.
    void draw(sf::RenderWindow &window) const;

    /// Sets a game's instance.
    void setGameInstance(Game *game_var);

};
