#pragma once
#include "Tank.hpp"
#include "Player.hpp"
#include "Sightline.hpp"

class YellowTank : public Tank{
    private:
        CustomHitbox collisionBox;
        SightLine sightline;

        double targetAngle;
        float projectileSpeed;
        int maxFireRate;

        double turnTimer;
        double total;
        int turnDir;
        int makeTurnTimer = GetRandomValue(180, 360);

        bool hasTarget;

        Rectangle body;
        Rectangle head;
        
        int ID;

        bool blockCollision(std::vector<Block*> blocks);

    public:
        char colorID = '0';

        YellowTank(double x, double y, double angle, int ID) {
            this->length = 32;
            this->width = 32;

            this->health = 1;
            this->fireRate = 420;
            this->maxFireRate = 420;
            this->projectileSpeed = 8.0;
            this->speed = 2;

            this->aimAngle = angle;
            this->angle = angle;
            this->targetAngle = angle;

            this->velocity.first = cos(angle);
            this->velocity.second = sin(angle);
            this->position.first = x;
            this->position.second = y;

            this->hitBox = CustomHitbox(0, 0, width, length);
            this->collisionBox = CustomHitbox(0, 0, width + 20, length + 20);

            this->hasTarget = false;
            this->turnTimer = 0;

            this->sightline = makeSightline({90, 282, 540}, {168, 264, 360});
            this->colorID = 'y';
            this->body = {264, 0, 64, 64};
            this->head = {616, 0, 153, 64};
            this->ID = ID;
        }

        void draw();
        void update();

        bool getHasTarget() { return this->hasTarget; }
        void setTurnTimer(int t) { this->makeTurnTimer = t; }
        void targetSystem(CustomHitbox target, std::vector<Block*> blocks);
        void move(std::vector<Block*> &blocks);
        void shoot(std::vector<Projectile*> &projectiles, std::pair<double, double> target);
        void drawHitboxes();
        void projectileCollision(std::vector<Projectile*> &projectiles);

        ~YellowTank() {}
};