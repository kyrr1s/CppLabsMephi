#include "Weapon.h"
#include "TileType.h"

///Trap that explodes
class Trap: public Weapon {

public:
    explicit Trap(ElementType elementType);

    void attack() override;

    void levelUp() override {};

    bool canBeLeveledUp() override {return false; };

    int getGold() const override {
        return 50;
    }

    TileType canBeBuilt() override;
};

