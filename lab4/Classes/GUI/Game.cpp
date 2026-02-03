#include "MainMenu.h"
#include "Game.h"


/**
 * @brief Sets the game icon, font, music, scene, frame limit
 */

Game::Game(): window(sf::VideoMode(600, 360), "MYFAROG", sf::Style::Titlebar | sf::Style::Close) {

    scene_manager.setGameInstance(this);

    // SFML doesn't have a standard cap of using GPU power, we need to set it (120 FPS)
    window.setFramerateLimit(120);

    //set music of the application
    if (!music.openFromFile("D:/prog/c++/lab4/cmake-build-debug/assets/mainMenuTheme.wav")) {
        MessageBox(nullptr, "Can not load mainMenuTheme.wav", "Error!", MB_OK);
        window.close();
    }
    music.play();
    music.setLoop(true);

    //set icon of the application
    if (!icon.loadFromFile("D:/prog/c++/lab4/cmake-build-debug/assets/icon.png")) {
        MessageBox(nullptr, "Can not load icon.png", "Error!", MB_OK);
        exit();
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //set the first scene, main menu
    scene_manager.setScene<MainMenu>();

}

/**
 * @brief Starts the main loop of the game.
 */

void Game::run() {
    sf::Clock clock;
    unsigned int last_frame;
    unsigned int catched_up_frames{0};
    constexpr unsigned int TIME_BETWEEN_UPDATED = 1000 / DELTA_TICKS;

    // Main loop of the game, used for checking events (e.g. clicking on buttons)
    while (window.isOpen()) {
        // Clears all previous events to check new ones
        event_manager.clear();

        EventStorage *event_storage = event_manager.checkForEvents(window);
        last_frame = clock.getElapsedTime().asMilliseconds();

        // Handles user actions
        while (last_frame - catched_up_frames > TIME_BETWEEN_UPDATED) {
            catched_up_frames += TIME_BETWEEN_UPDATED;

            // FixedUpdate can run once, zero, or several times per frame,
            // depending on how many physics frames per second are set in the time settings,
            // and how fast/slow the framerate is
            scene_manager.fixedUpdate(event_storage);
        }

        //Update runs once per frame
        scene_manager.update(event_storage);

        //Render window
        window.clear();
        scene_manager.draw(window);
        window.display();
    }
}

/**
 * @return A SFML object of a main window of a game.
 */

sf::RenderWindow *Game::getWindow() {
    return &window;
}

/**
 * @return A scene manager of an engine.
 */

SceneManager *Game::getSceneManager() {
    return &scene_manager;
}

/**
 * @brief Closes the game.
 */

void Game::exit() {
    window.close();
}

