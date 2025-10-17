#pragma once
#include "EnemyTank.hpp"

class GreenTank : public Enemy {
    public:
        GreenTank(double x, double y, double angle, int ID) : Enemy(x, y, angle, 120, 4.0) { 
            this->colorID = 'g'; 
            this->body = {132, 0, 64, 64};
            this->head = {308, 0, 153, 64};
            this->ID = ID;
        }

        void updateAll(Tank* player, std::vector<Projectile*> &projectiles, std::vector<Block*> blocks) override {
            this->update();
            this->targetSystem(player->getHitbox(), blocks);
            this->move(blocks);
            this->shoot(projectiles, player->getPosition());
        }
};

