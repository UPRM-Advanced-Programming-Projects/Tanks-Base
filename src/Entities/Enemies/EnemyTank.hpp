#pragma once
#include "Tank.hpp"
#include "Player.hpp"

enum Direction {
    UP = 270,
    DOWN = 90, 
    LEFT = 180,
    RIGHT = 0
};

struct SightLine {
    std::vector<CustomHitbox> hitboxes;
    std::vector<double> distances;
};

SightLine makeSightline(std::vector<double> distances, std::vector<double> sizes);

class Enemy : public Tank {
    protected:
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
        
        Enemy(double x, double y, double angle, int maxFireRate, float projectileSpeed) {
            this->length = 32;
            this->width = 32;

            this->health = 1;
            this->fireRate = maxFireRate;
            this->maxFireRate = maxFireRate;
            this->projectileSpeed = projectileSpeed;
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

            sightline = makeSightline({90, 282}, {168, 264});

            this->hasTarget = false;
            this->turnTimer = 0;
            
        }

        void draw() override;
        void update() override;

        bool getHasTarget() { return this->hasTarget; }
        void setTurnTimer(int t) { this->makeTurnTimer = t; }
        void targetSystem(CustomHitbox target, std::vector<Block*> blocks);
        void move(std::vector<Block*> &blocks);
        void shoot(std::vector<Projectile*> &projectiles, std::pair<double, double> target);
        void drawHitboxes();
        void projectileCollision(std::vector<Projectile*> &projectiles);
        static void allyCollision(std::vector<Enemy*> allies);

        virtual void updateAll(Tank* player, std::vector<Projectile*> &projectiles, std::vector<Block*> blocks) = 0;

        virtual ~Enemy() {}
};