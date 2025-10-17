#pragma once
#include "Projectile.hpp"

class HomingMissile : public Projectile {
    protected:
        std::pair<double, double> target;
        std::pair<double, double> velocity;
        double angle;
        double targetAngle;
        float speed;

    public:
        HomingMissile(double x, double y, float speed, std::pair<double, double> target, int ID) : Projectile(x, y, 0) {
            this->position.first = x;
            this->position.second = y;
            this->speed = speed;
            this->angle = (180 / PI) * atan2((target.second - y), (target.first - x));
            this->targetAngle = 
            this->velocity.first = cos(angle * PI / 180);
            this->velocity.second = sin(angle * PI / 180);
            this->hitbox.setSize(8, 8);
            this->ID = ID;
        }

        void update(std::vector<Block*> blocks, CustomHitbox target) override;
        void draw() override;
        void chaseTarget(std::pair<double, double> targetPos);

};