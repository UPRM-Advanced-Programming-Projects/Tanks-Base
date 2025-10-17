#pragma once

#include <iostream>
#include <string>
#include "raylib-cpp/raylib-cpp.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "State.hpp"
#include "Animation.hpp"

class Game : public State {
    public:
        Game() {
            this->name = "GAME";
            currentMap = 1;
            world = Map::getMap(currentMap);
            player->setPosition(world.getX(), world.getY());
            player->setDirection(world.getAngle());
        }
        
        void setCounter(Counter* counter) { this->counter = counter; }
        void Update() override;
        void Draw() override;
        void KeyPressed(int key) override;
        void KeyReleased() override;
        void MousePressed(int x, int y, int button) override;
        void Reset() override;
        void manageAnimations();
        
        int currentMap;	  
        bool win = false;
        bool nextLevel = false;
        bool startUp = true;
        int delay = 100;
        std::vector<Projectile*> projectiles;
        Player* player = new Player();
        Map world;
        Counter* counter;

        ~Game() {}
};