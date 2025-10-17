#pragma once
#include "EnemyTank.hpp"
#include "Mine.hpp"

class RedTank : public Enemy {
    public:
        RedTank(double x, double y, double angle, int ID) : Enemy(x, y, angle, 420, 0) {
            sightline = makeSightline({0}, {0});
            this->colorID = 'r';
            this->body = {198, 0, 64, 64};
            this->head = {462, 0, 153, 64};
            this->ID = ID;
        }

        void placeMine(std::vector<Projectile*> &projectiles) {
            if (fireRate <= 0) {
                PlaySound(SoundManager::shoot);
                Mine* m = new Mine(this->position.first, this->position.second);
                projectiles.push_back(m);
                this->fireRate = maxFireRate;
            }
        }

        void updateAll(Tank* player, std::vector<Projectile*> &projectiles, std::vector<Block*> blocks) override {
            this->update();
            this->move(blocks);
            this->placeMine(projectiles);
        }
};