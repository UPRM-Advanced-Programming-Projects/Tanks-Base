#pragma once
#include "EnemyTank.hpp"

class PinkTank : public Enemy {
    public:
        PinkTank(double x, double y, double angle, int ID) : Enemy(x, y, angle, 120, 6.0) { 
            this->colorID = 'P'; 
            this->body = {462, 0, 64, 64};
            this->head = {1078, 0, 153, 64};
            this->ID = ID;
        }

        void shoot(std::vector<Projectile*> &projectiles, Tank* player) {
            std::pair<double, double> target = player->getPosition();
            if (player->isMoving()) {
                target = Math::getPointOfIntersection(this->projectileSpeed, this->position, player->getSpeed(), 
                player->getPosition(), player->getVelocity());
            }
            
            if (fireRate <= 0 && this->hasTarget) {
                PlaySound(SoundManager::shoot);
                Missile* m = new Missile(this->position.first, this->position.second, 2, this->projectileSpeed, target, this->ID);
                projectiles.push_back(m);
                this->fireRate = maxFireRate;
            }
        }

        void updateAll(Tank* player, std::vector<Projectile*> &projectiles, std::vector<Block*> blocks) override {
            this->update();
            this->targetSystem(player->getHitbox(), blocks);
            this->move(blocks);
            this->shoot(projectiles, player);
        }

};