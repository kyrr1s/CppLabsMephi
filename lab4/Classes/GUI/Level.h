#pragma once

#include "MapObject.h"
#include "TileGUI.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <algorithm>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Mouse.hpp>
#include "../../tinyxml/tinyxml2.h"

/// Reads map from XML file

/// In TMX maps, a layer is a set of tiles_sprites (sprites) that make up the landscape of the map.
struct Layer {
    sf::Uint8 opacity = 0;
    std::vector<sf::Sprite> tiles_sprites;
};

class Level {

    /// Width of level in tiles_sprites.
    int width = 0;

    /// Height of level in tiles_sprites.
    int height = 0;

    int first_tileID = 0;

    sf::Texture tileset_texture;

    /// Game objects on that level, that can be moved.
    std::vector<MapObject> objects;

    /// Layers to render.
    std::vector<Layer> layers;

    std::vector<TileGUI> tiles_gui;

public:

    int TILE_SIZE;

    /// Sets all fields from file.
    void loadFromFile(const std::string &filepath);

    /// Gets first object with that name.
    MapObject getFirstObject(const std::string &name) const;

    /// Gets vector of all objects with that name.
    std::vector<MapObject> getAllObjects(const std::string &name) const;

    /// Gets width of a map.
    float getTilemapWidth() const;

    /// Gets height of a map.
    float getTilemapHeight() const;

    /// Gets size of a map.
    sf::Vector2f getTilemapSize() const;

    /// Renders all layers, but not objects.
    void draw(sf::RenderTarget & target) const;

    /// Sets tiles_gui vec.
    void constructTiles();

    ///Gets a tile from a mouse.
    TileGUI* getTileFromMouse(sf::Vector2<float> vector, const sf::Window& window);

    ///Gets a tile from window position. This function is used, to calculate to find the position
    ///on where to position the enemy and/or weapons.
    sf::Vector2<int> getTileWindowPosition(TileGUI* tile, const sf::Window& window);

    ///Gets a tile from a coordinate.
    TileGUI* getTileFromCoordinate(sf::Vector2<int> position) ;

    ///Gets a tile from coordinate (or from window, if that did not work).
    sf::Vector2<int> getTileWindowPositionFromTileCoordinate(sf::Vector2<int> coordinate, const sf::Window& window);

    std::vector<TileGUI> getTiles() const;
};
