#pragma once
#include "Block.hpp"
#include "GreenTank.hpp"
#include "PinkTank.hpp"
#include "BeigeTank.hpp"
#include "YellowTank.hpp"
#include "RedTank.hpp"
#include "PurpleTank.hpp"
#include "WhiteTank.hpp"
#include "LimeTank.hpp"
#include "BlackTank.hpp"

#define Width GetScreenWidth()
#define Height GetScreenHeight()

class Map {
    protected:
        std::vector<Block*> layout;
        std::vector<Enemy*> enemies;
        std::pair<double, double> playerStart;
        double startAngle;
        
    public:
        bool showHitboxes = false;
        inline static int ID = 1;

        Map(double x, double y, double angle) {
            playerStart.first = x;
            playerStart.second = y;
            startAngle = angle;

            layout.push_back(new Block(0, 0, Width * 2, 10));
            layout.push_back(new Block(0, 0, 10, Height * 2));
            layout.push_back(new Block(Width, 0, 10, Height * 2));
            layout.push_back(new Block(0, Height, Width * 2, 10));
        }

        Map() {
            playerStart.first = 0;
            playerStart.second = 0;

            layout.push_back(new Block(0, 0, Width * 2, 10));
            layout.push_back(new Block(0, 0, 10, Height * 2));
            layout.push_back(new Block(Width, 0, 10, Height * 2));
            layout.push_back(new Block(0, Height, Width * 2, 10));
        }
        
        double getX() { return this->playerStart.first; }
        double getY() { return this->playerStart.second; }
        double getAngle() { return this->startAngle; }
        
        std::vector<Block*> getLayout() { return this->layout; }
        std::vector<Enemy*> getEnemies() { return this->enemies; }
        void addBlock(Block* b) { this->layout.push_back(b); }
        void addEnemy(Enemy* e) { this->enemies.push_back(e); }
        std::vector<CustomHitbox> getEnemyHitboxes() {
            std::vector<CustomHitbox> hitboxes;
            for (Enemy* e : this->enemies) hitboxes.push_back(e->getHitbox());
            return hitboxes;
        }

        void draw();
        void update(Player* &player, std::vector<Projectile*> &projectiles);
        void enemyCollisions();
        static Map getMap(int level);
};