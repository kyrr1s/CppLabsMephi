#pragma once

#include "Scene.h"
#include "MenuOption.h"

#include <vector>

/// Next scene after main menu. A player should choose a level to play.
class LevelMenu : public Scene {

    //todo: should I do a vector of buttons?

    sf::Text back_button_text;
    MenuOption back_button;

    sf::Text prev_level_text;
    MenuOption prev_level_button;

    sf::Text next_level_text;
    MenuOption next_level_button;

    sf::Text current_level_text;

    sf::Text play_button_text;
    MenuOption play_button;

    std::vector<std::string> levels_name;
    size_t current_level_num;

    /// Fills levels_name vector with all levels names. The minimum required number of levels is one.
    void parseLevels();

    /// Sets the new value of a number of current level.
    void swapLevel(size_t level);

    /// Checks if there is a next level (or current level is the last level).
    bool hasNextLevel();

    /// Checks if there is a previous level (or current level is the first level).
    bool hasPrevLevel() const;

    /// Gets level name.
    std::string getLevelName();

    /// Recheck the status of previous, next and current levels buttons. Change them, if they should be inactive. Sets the name of a current level.
    void updateBindings();

public:

    /// Create a basic scene without any buttons.
    LevelMenu() : Scene(), current_level_num(0) {}

    void enter(Game *game) override;

    void setGUI(Game *game) override;

    void draw(sf::RenderWindow &window) const override;
};

