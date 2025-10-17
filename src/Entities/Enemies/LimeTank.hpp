#pragma once
#include "EnemyTank.hpp"
#include "HomingMissile.hpp"

class LimeTank : public Enemy {
    public:
        LimeTank(double x, double y, double angle, int ID) : Enemy(x, y, angle, 120, 4.0) { 
            this->sightline = makeSightline({90, 282, 540}, {168, 264, 360});
            this->colorID = 'l'; 
            this->body = {528, 0, 64, 64};
            this->head = {1232, 0, 153, 64};
            this->ID = ID;
        }

        void shootHoming(std::vector<Projectile*> &projectiles, std::pair<double, double> target) {
            if (fireRate <= 0 && this->hasTarget) {
                PlaySound(SoundManager::shoot);
                HomingMissile* m = new HomingMissile(this->position.first, this->position.second,
                                                    this->projectileSpeed, target, this->ID);
                projectiles.push_back(m);
                this->fireRate = maxFireRate;
            }
        }

        void updateAll(Tank* player, std::vector<Projectile*> &projectiles, std::vector<Block*> blocks) override {
            this->update();
            this->targetSystem(player->getHitbox(), blocks);
            this->move(blocks);
            this->shootHoming(projectiles, player->getPosition());
        }
};