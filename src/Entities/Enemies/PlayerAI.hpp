#pragma once
#include "Tank.hpp"
#include "Player.hpp"
#include "Sightline.hpp"
#include "MathUtils.hpp"

class PlayerAI {
    private:
        double length;
        double width;

        int health;
        int fireRate;
        float speed;
        bool moving = false;
        
        double aimAngle;
        double angle;
        std::pair<double, double> velocity;
        std::pair<double, double> position;

        CustomHitbox hitBox;
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

    public:
        char colorID = '0';

        PlayerAI(double x, double y, double angle, int ID) {
            this->length = 32;
            this->width = 32;

            this->health = 1;
            this->fireRate = 120;
            this->maxFireRate = 120;
            this->projectileSpeed = 4.0;
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
            this->body = {2, 0, 64, 64};
            this->head = {0, 0, 153, 64};
            this->ID = ID;
        }

        void draw();
        void update();

        int getHealth() { return this->health; }
        float getSpeed() { return this->speed; }
        bool isMoving() { return this->moving; }
        CustomHitbox getHitbox() { return this->hitBox; }
        std::pair<double, double> getPosition() { return this->position; }
        std::pair<double, double> getVelocity() { return this->velocity; }
        bool getHasTarget() { return this->hasTarget; }
        void setTurnTimer(int t) { this->makeTurnTimer = t; }

        void targetSystem(CustomHitbox target, std::vector<Block*> blocks);
        void move(std::vector<Block*> &blocks);
        void shoot(std::vector<Projectile*> &projectiles, std::pair<double, double> pos, std::pair<double, double> vel, float speed, bool isMoving);
        void drawHitboxes();
        void projectileCollision(std::vector<Projectile*> &projectiles);
        void trackTarget(CustomHitbox target, std::vector<Block*> blocks);


        // void updateAll(Tank* enemy, std::vector<Projectile*> &projectiles, std::vector<Block*> blocks) override {
        //     this->update();
        //     this->targetSystem(enemy->getHitbox(), blocks);
        //     this->shoot(projectiles, enemy);
        //     this->trackTarget(enemy->getHitbox(), blocks);
        //     this->move(blocks);
        // }

};