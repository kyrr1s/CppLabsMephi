#include "LevelMenu.h"
#include "Game.h"
#include "MainMenu.h"
#include "GameMenu.h"

void LevelMenu::draw(sf::RenderWindow &window) const {

    window.draw(back_button);
    window.draw(current_level_text);
    window.draw(prev_level_button);
    window.draw(next_level_button);
    window.draw(play_button);

}

void LevelMenu::parseLevels() {
    levels_name.emplace_back("Level1");
    levels_name.emplace_back("Test level2");
    levels_name.emplace_back("Test level3");
    levels_name.emplace_back("Test level4");
}

void LevelMenu::swapLevel(size_t level) {
    current_level_num = level;
    updateBindings();
}

bool LevelMenu::hasNextLevel() {
    return current_level_num + 1 < levels_name.size();
}

bool LevelMenu::hasPrevLevel() const {
    return current_level_num != 0;
}

std::string LevelMenu::getLevelName() {

    if (current_level_num < levels_name.size()) return levels_name[current_level_num];

    return "No Levels Available!";
}

void LevelMenu::setGUI(Game *game) {
    //todo: should I do special functions-setters for all that buttons?

    back_button_text.setString("Back");
    back_button_text.setFont(font);
    back_button_text.setCharacterSize(20);

    back_button = createElement<MenuOption>(back_button_text);
    back_button.setColor(sf::Color{122, 20, 37});
    back_button.setPosition(0.f, 50.f);
    back_button.setClickHandler([game]() { game->getSceneManager()->setScene<MainMenu>(); });
    pushElement(&back_button);

    prev_level_text.setFont(font);
    prev_level_text.setCharacterSize(30);
    prev_level_text.setString("Prev");

    prev_level_button = createElement<MenuOption>(prev_level_text, 100.f, 60.f);
    prev_level_button.setColor(sf::Color{130, 20, 37});
    prev_level_button.setPosition(200.f, 100.f);
    prev_level_button.setClickHandler([this]() {
        swapLevel(--current_level_num);
    });
    pushElement(&prev_level_button);

    next_level_text.setFont(font);
    next_level_text.setCharacterSize(30);
    next_level_text.setString("Next");

    next_level_button = createElement<MenuOption>(next_level_text, 100.f, 60.f);
    next_level_button.setColor(sf::Color{130, 20, 37});
    next_level_button.setPosition(310.f, 100.f);
    next_level_button.setClickHandler([this]() {
        swapLevel(++current_level_num);
    });
    pushElement(&next_level_button);

    current_level_text.setFont(font);
    current_level_text.setCharacterSize(50);
    current_level_text.setString(getLevelName());
    current_level_text.setPosition(200.f, 40.f);

    play_button_text.setFont(font);
    play_button_text.setString("Play!");

    play_button = createElement<MenuOption>(play_button_text, 210.f, 60.f);
    play_button.setPosition(200.f, 180.f);
    play_button.setColor(sf::Color{65, 161, 18});
    play_button.setClickHandler([this, game]() { game->getSceneManager()->setScene<GameMenu>(getLevelName()); });
    pushElement(&play_button);
}

void LevelMenu::enter(Game *game) {
    parseLevels();
    updateBindings();
}

void LevelMenu::updateBindings() {
    play_button.setDisabled(levels_name.empty());
    prev_level_button.setDisabled(!hasPrevLevel());
    next_level_button.setDisabled(!hasNextLevel());
    current_level_text.setString(getLevelName());
}
