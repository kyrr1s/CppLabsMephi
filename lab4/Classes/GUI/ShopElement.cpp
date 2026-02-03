#include "ShopElement.h"
#include "../GameLogic/Tower.h"
#include "../GameLogic/Trap.h"

#include <utility>


ShopElement::ShopElement(ElementType weaponType, sf::Text weaponText, sf::Text goldText) : GUI_Element({50.f, 50.f}),
                                                                                           weapon_type(weaponType),
                                                                                           weapon_name(std::move(weaponText)),
                                                                                           gold_text(std::move(goldText)) {
    background.setSize({50.f, 50.f});
    background.setFillColor(sf::Color{128, 128, 128, 64});

    background.setPosition(10.f, 10.f);

    weapon_name.setCharacterSize(10);
    gold_text.setCharacterSize(13);

    weapon_name.setPosition(15.f, 25.f);
    gold_text.setPosition(15.f, 40.f);
}

void ShopElement::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(background, states);
    target.draw(weapon_name, states);
    target.draw(gold_text, states);
}

std::shared_ptr<WeaponGUI> ShopElement::getTower(float tile_size) const {
    std::shared_ptr<Tower> tower = std::make_shared<Tower>(weapon_type);
    std::shared_ptr<WeaponGUI> weapon = std::make_shared<WeaponGUI>(weapon_type, tile_size);
    weapon->setWeapon(tower);
    return weapon;
}

std::shared_ptr<WeaponGUI> ShopElement::getTrap(float tile_size) const {
    std::shared_ptr<Trap> trap = std::make_shared<Trap>(weapon_type);
    std::shared_ptr<WeaponGUI> weapon = std::make_shared<WeaponGUI>(weapon_type, tile_size);
    weapon->setWeapon(trap);
    return weapon;
}

void ShopElement::setColor(sf::Color color) {
    background.setFillColor(color);
}