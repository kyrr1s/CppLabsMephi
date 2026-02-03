#include "MainMenu.h"

#include "Game.h"
#include "LevelMenu.h"

void MainMenu::draw(sf::RenderWindow &window) const {
    window.draw(play_button);
    window.draw(exit_button);
}

void MainMenu::setGUI(Game *game) {
    //todo: should I do special functions-setters for all that buttons?

    play_button_text.setFont(font);
    play_button_text.setString("Play!");
    play_button_text.setCharacterSize(30);

    play_button = createElement<MenuOption>(play_button_text, 200.f, 50.f);
    play_button.setColor(sf::Color{214, 47, 75});
    play_button.setPosition(0.f, 100.f);
    // Not mutable, because we do not want to change game engine.
    play_button.setClickHandler([game]() { game->getSceneManager()->setScene<LevelMenu>(); });

    pushElement(&play_button);

    exit_button_text.setFont(font);
    exit_button_text.setString("Quit");
    exit_button_text.setCharacterSize(20);

    exit_button = createElement<MenuOption>(exit_button_text, 150.f, 20.f);
    exit_button.setColor(sf::Color{122, 20, 37});
    exit_button.setPosition(0.f, 175.f);
    // Not mutable, because we do not want to change game engine.
    exit_button.setClickHandler([game]() { game->getWindow()->close(); });

    pushElement(&exit_button);
}
