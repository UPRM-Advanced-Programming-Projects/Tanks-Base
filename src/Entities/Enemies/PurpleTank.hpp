#pragma once
#include "EnemyTank.hpp"
#include "HomingMissile.hpp"

#define X this->position.first
#define Y this->position.second

class PurpleTank : public Enemy {
    public:
        PurpleTank(double x, double y, double angle, int ID) : Enemy(x, y, angle, 120, 3.0) {
            this->sightline = makeSightline({90, 282, 540}, {168, 264, 360});
            this->collisionBox.setPosition(X, Y);
            this->colorID = 'p';
            this->body = {330, 0, 64, 64};
            this->head = {770, 0, 153, 64};
            this->ID = ID;
        }

        void staticUpdate() {
            this->fireRate = std::max(this->fireRate - 1, 0);
            this->hitBox.setPosition(X, Y);

            for (int i = 0; i < sightline.hitboxes.size(); i++) {
                double dist = sightline.distances[i];
                sightline.hitboxes[i].setPosition(X + dist * cos(this->aimAngle * PI/180), Y + dist * sin(this->aimAngle * PI/180));
            }

            double angleDiff = Math::getAngleDif(this->aimAngle, this->targetAngle);

            if (!this->hasTarget) {
                this->targetAngle += 0.5;
            }

            this->aimAngle -= this->hasTarget ? angleDiff / 5 : angleDiff / 25;
            if (this->aimAngle > 360.0) this->aimAngle -= 360.0;
            if (this->aimAngle <   0.0) this->aimAngle += 360.0;

        }

        void shootHoming(std::vector<Projectile*> &projectiles, std::pair<double, double> target) {
            if (fireRate <= 0 && this->hasTarget) {
                PlaySound(SoundManager::shoot);
                HomingMissile* m = new HomingMissile(X, Y, this->projectileSpeed, target, this->ID);
                projectiles.push_back(m);
                this->fireRate = maxFireRate;
            }
        }

        void updateAll(Tank* player, std::vector<Projectile*> &projectiles, std::vector<Block*> blocks) override {
            this->staticUpdate();
            this->targetSystem(player->getHitbox(), blocks);
            this->shootHoming(projectiles, player->getPosition());
        }
    
};

