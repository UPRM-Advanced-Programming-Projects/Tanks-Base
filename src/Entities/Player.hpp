#pragma once
#include "Tank.hpp"
#include "Mine.hpp"

class Player : public Tank {
    public:
        bool rotateLeft = false;
        bool rotateRight = false;
        bool moveForward = false;
        bool moveBackward = false;
        int lives = 3;

        Player() {
            this->length = 32;
            this->width = 32;

            this->health = 1;
            this->fireRate = 0;
            this->speed = 3;

            this->aimAngle = 0;
            this->angle = 0;

            this->velocity.first = cos(angle);
            this->velocity.second = sin(angle);
            this->position.first = GetScreenWidth() / 2;
            this->position.second = GetScreenHeight() / 2;

            this->hitBox = CustomHitbox(0, 0, width, length);
        }

        Player(double x, double y) {
            this->length = 32;
            this->width = 32;

            this->health = 1;
            this->fireRate = 0;
            this->speed = 3;

            this->aimAngle = 0;
            this->angle = 0;

            this->velocity.first = cos(angle);
            this->velocity.second = sin(angle);
            this->position.first = x;
            this->position.second = y;

            this->hitBox = CustomHitbox(0, 0, width, length);       
        }

        void setDirection(double angle) {
            this->angle = angle;
            this->aimAngle = angle;
        }
        
        void update() override;
        void draw() override;
        void shoot(std::vector<Projectile*> &projectiles);
        void projectileCollision(std::vector<Projectile*> &projectiles);

        void rotate(int dir) { this->angle += dir * 2; }
        void move() { 
            this->position.first += this->velocity.first * this->speed; 
            this->position.second += this->velocity.second * this->speed;
        }

        void controls(std::vector<Block*> &border, std::vector<CustomHitbox> enemies);

};