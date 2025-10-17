#pragma once
#include "EnemyTank.hpp"

class YellowTank : public Enemy {
    public:
        YellowTank(double x, double y, double angle, int ID) : Enemy(x, y, angle, 120, 8.0) {
            this->sightline = makeSightline({90, 282, 540}, {168, 264, 360});
            this->colorID = 'y';
            this->body = {264, 0, 64, 64};
            this->head = {616, 0, 153, 64};
            this->ID = ID;
        }

        void updateAll(Tank* player, std::vector<Projectile*> &projectiles, std::vector<Block*> blocks) override {
            this->update();
            this->targetSystem(player->getHitbox(), blocks);
            this->move(blocks);
            this->shoot(projectiles, player->getPosition());
        }
};