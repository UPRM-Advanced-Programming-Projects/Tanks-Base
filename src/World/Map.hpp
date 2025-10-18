#pragma once
#include "Block.hpp"
#include "GreenTank.hpp"
#include "BeigeTank.hpp"
#include "YellowTank.hpp"
#include "RedTank.hpp"

#define Width GetScreenWidth()
#define Height GetScreenHeight()

class Map {
    protected:
        std::vector<Block*> layout;
        std::pair<double, double> playerStart;
        double startAngle;
        
    public:
        std::vector<BeigeTank*> enemies1;
        std::vector<GreenTank*> enemies2;
        std::vector<RedTank*> enemies3;
        std::vector<YellowTank*> enemies4;

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
        int getEnemyCount() { return this->enemies1.size() + this->enemies2.size() + this->enemies3.size() + this->enemies4.size(); }
        
        std::vector<Block*> getLayout() { return this->layout; }

        void addBlock(Block* b) { this->layout.push_back(b); }
        void addBeige(BeigeTank* e) { this->enemies1.push_back(e); }
        void addGreen(GreenTank* e) { this->enemies2.push_back(e); }
        void addRed(RedTank* e) { this->enemies3.push_back(e); }
        void addYellow(YellowTank* e) { this->enemies4.push_back(e); }

        std::vector<CustomHitbox> getEnemyHitboxes() {
            std::vector<CustomHitbox> hitboxes;
            for (BeigeTank* e : this->enemies1) hitboxes.push_back(e->getHitbox());
            for (GreenTank* e : this->enemies2) hitboxes.push_back(e->getHitbox());
            for (RedTank* e : this->enemies3) hitboxes.push_back(e->getHitbox());
            for (YellowTank* e : this->enemies4) hitboxes.push_back(e->getHitbox());
            return hitboxes;
        }

        void draw();
        void update(Player* &player, std::vector<Projectile*> &projectiles);
        void enemyCollisions();
        static Map getMap(int level);
};