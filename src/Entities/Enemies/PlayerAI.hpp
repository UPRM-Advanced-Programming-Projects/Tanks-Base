#pragma once
#include "EnemyTank.hpp"

class PlayerAI : public Enemy {
    public:
        PlayerAI(double x, double y, double angle, int ID) : Enemy(x, y, angle, 120, 4.0) {
            this->sightline = makeSightline({90, 282, 540}, {168, 264, 360});
            this->colorID = '0';
            this->body = {2, 0, 64, 64};
            this->head = {0, 0, 153, 64};
            this->ID = ID;
        }

        void shoot(std::vector<Projectile*> &projectiles, Tank* enemy) {
            std::pair<double, double> target = enemy->getPosition();
            if (enemy->isMoving()) {
                target = Math::getPointOfIntersection(this->projectileSpeed, this->position, enemy->getSpeed(), 
                enemy->getPosition(), enemy->getVelocity());
            }
            
            if (fireRate <= 0 && this->hasTarget) {
                PlaySound(SoundManager::shoot);
                Missile* m = new Missile(this->position.first, this->position.second, 2, this->projectileSpeed, target, this->ID);
                projectiles.push_back(m);
                this->fireRate = maxFireRate;
            }
        }

        void trackTarget(CustomHitbox target, std::vector<Block*> blocks) {
            double angleToTarget = Math::atan3(target.box.y - this->position.second, 
                                            target.box.x - this->position.first);

            double angleDiff = Math::getAngleDif(this->angle, angleToTarget);
        
            if (this->hasTarget && Math::getDistance(this->hitBox, target) >= 100) {
                this->angle -= angleDiff / 10;
                this->position.first += this->velocity.first * speed;
                this->position.second += this->velocity.second * speed;

                for (Block* b : blocks) {
                    if (CustomHitbox::collision(this->collisionBox, b->getHitbox())) {
                        std::pair<double, double> collision = CustomHitbox::collisionMargins(this->collisionBox, b->getHitbox());
                        if (abs(collision.second) < abs(collision.first)) {
                            this->position.second += collision.second - Math::sign(this->velocity.second);
                        } else {
                            this->position.first += collision.first - Math::sign(this->velocity.first);
                        }
                    }
                }

            }
            
            if (this->angle > 360.0) this->aimAngle -= 360.0;
            if (this->angle <   0.0) this->aimAngle += 360.0;

        }

        void entityCollision(std::vector<Enemy*> enemies) {
            for (Enemy* e : enemies) {
                if (CustomHitbox::collision(e->getHitbox(), this->getHitbox())) {
                    this->makeTurnTimer = 0;
                    e->setTurnTimer(0);
                }
            }
        }

        void updateAll(Tank* enemy, std::vector<Projectile*> &projectiles, std::vector<Block*> blocks) override {
            this->update();
            this->targetSystem(enemy->getHitbox(), blocks);
            this->shoot(projectiles, enemy);
            this->trackTarget(enemy->getHitbox(), blocks);
            this->move(blocks);
        }

};