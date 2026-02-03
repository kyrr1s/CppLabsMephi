#pragma once

#include "../baseHeaders.h"

#include "SceneManager.h"
#include "EventManager.h"
#define DELTA_TICKS 60

//! Engine of a game.
class Game: sf::NonCopyable {

    /// Main window of GUI
    sf::RenderWindow window;

    /// Handler for various scenes, needed to draw and update them
    SceneManager scene_manager;

    /// Handler for various events, needed to process them in right order and their function
    EventManager event_manager;

    /// Some cosmetic for the main game
    sf::Image icon;
    sf::Music music;

public:

    Game();

    ~Game() = default;

    sf::RenderWindow *getWindow();

    SceneManager *getSceneManager();

    void run();

    void exit();
};