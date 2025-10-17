#pragma once
#include "Projectile.hpp"

class Mine : public Projectile {
    private:
        int mult = -1;
        int timer = 90;
        int color = 255;

    public:
        CustomHitbox collisionBox;

        Mine(double x, double y) : Projectile(x, y, 0) {
            this->hitbox.setSize(20, 20);
            this->hitbox.setPosition(x, y);
            this->collisionBox = CustomHitbox(x, y, 110, 110);
            this->ID = -1;
        }

        void draw() override;
        void update(std::vector<Block*> blocks, CustomHitbox target) override;

};