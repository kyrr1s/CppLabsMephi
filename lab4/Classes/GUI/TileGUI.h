#pragma once

#include <utility>

#include "../GameLogic/Tile.h"

class TileGUI {
    Tile tile;
    sf::Sprite sprite;

public:

    using Ptr = std::shared_ptr<TileGUI>;

    TileGUI(Tile tile_var, sf::Sprite tile_sprite): sprite(std::move(tile_sprite)) {
        tile = std::move(tile_var);
    }

    Tile& getTile() {
        return tile;
    }

    const Tile& getTile() const {
        return tile;
    }

    const sf::Sprite& getSprite() const {
        return sprite;
    }


};

