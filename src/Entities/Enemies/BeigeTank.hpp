#pragma once
#include "EnemyTank.hpp"

#define X this->position.first
#define Y this->position.second

class BeigeTank : public Enemy {
    public:
        BeigeTank(double x, double y, double angle, int ID) : Enemy(x, y, angle, 120, 4.0) {
            this->collisionBox.setPosition(X, Y);
            this->colorID = 'b';
            this->body = {66, 0, 64, 64};
            this->head = {154, 0, 153, 64};
            this->ID = ID;
        }

        void staticUpdate() {
            this->fireRate = std::max(this->fireRate - 1, 0);
            this->collisionBox.setPosition(X, Y);
            this->hitBox.setPosition(X, Y);

            for (int i = 0; i < sightline.hitboxes.size(); i++) {
                double dist = sightline.distances[i];
                sightline.hitboxes[i].setPosition(X + dist * cos(this->aimAngle * PI/180), 
                                                  Y + dist * sin(this->aimAngle * PI/180));
            }

            double angleDiff = Math::getAngleDif(this->aimAngle, this->targetAngle);
            if (!this->hasTarget) { this->targetAngle += 0.5; }

            this->aimAngle -= this->hasTarget ? angleDiff / 5 : angleDiff / 25;
            if (this->aimAngle > 360.0) this->aimAngle -= 360.0;
            if (this->aimAngle <   0.0) this->aimAngle += 360.0;

        }

        void updateAll(Tank* player, std::vector<Projectile*> &projectiles, std::vector<Block*> blocks) override {
            this->staticUpdate();
            this->targetSystem(player->getHitbox(), blocks);
            this->shoot(projectiles, player->getPosition());
        }
    
};

