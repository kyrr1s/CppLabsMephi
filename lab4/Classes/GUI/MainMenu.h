#pragma once
#include "Scene.h"
#include "MenuOption.h"

#include <functional>

#include <SFML/Graphics/Text.hpp>

/// The first scene of a game, where a player should choose: play or leave.
class MainMenu: public Scene {

    /// A play button.
    sf::Text play_button_text;
    MenuOption play_button;

    /// An exit button.
    sf::Text exit_button_text;
    MenuOption exit_button;

    //todo: should I create a vector of buttons?

public:

    /// Create a basic scene without any buttons.
    explicit MainMenu():Scene(){}

    void setGUI(Game *game) override;

    void draw(sf::RenderWindow &window) const override;


};