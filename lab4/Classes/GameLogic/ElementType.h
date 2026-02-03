#pragma once
#include <SFML/System.hpp>

//! Possible element types.
enum ElementType : sf::Uint8 {
    ///Base elements
    Hydro,
    Dendro,
    Cryo,
    Pyro,
    Electro,
    ///Helpful element that does nothing
    None,
    Canselled,
    ///Results of reactions
    Overloading,
    Melting2x,
    Melting1and5x,
    Slowing,
    Charge,
    Weakening,
    Steam,
    Stimulation,
    Blossom,
    Burning,
    Split,

};
