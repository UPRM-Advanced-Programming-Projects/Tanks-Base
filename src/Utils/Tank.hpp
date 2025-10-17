#pragma once
#include "HitBox.hpp"
#include "Missile.hpp"
#include "Block.hpp"
#include "MathUtils.hpp"
#include "Animation.hpp"
#include "SoundManager.hpp"

class Tank {
    protected:
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
        
    public:
        inline static Texture2D tankBodies;
        inline static Texture2D tankHeads;
        inline static Texture2D tankExplosion;
        inline static std::vector<Animation> animations;

        Tank() {}

        virtual void update() = 0;
        virtual void draw() = 0;

        int getHealth() { return this->health; }
        float getSpeed() { return this->speed; }
        bool isMoving() { return this->moving; }
        CustomHitbox getHitbox() { return this->hitBox; }
        std::pair<double, double> getPosition() { return this->position; }
        std::pair<double, double> getVelocity() { return this->velocity; }

        void setHealth(int h) {
            this->health = h;
        }
        
        void setPosition(double x, double y) {
            this->position.first = x;
            this->position.second = y;
        }

        static void LoadImages() {
            tankBodies = LoadTextureFromImage(LoadImage("images/TankBodies.png"));
            tankHeads = LoadTextureFromImage(LoadImage("images/TankHeads.png"));
            tankExplosion = LoadTextureFromImage(LoadImage("images/TankExplosion.png"));
        }

        static void UnloadImages() {
            UnloadTexture(tankBodies);
            UnloadTexture(tankHeads);
            UnloadTexture(tankExplosion);
        }

        ~Tank() {}
};