#pragma once
#include "Map.hpp"
#include "PlayerAI.hpp"
#include "State.hpp"

class Intro : public State {
    protected:
        std::vector<Block*> layout;
        std::vector<BeigeTank*> enemies1;
        std::vector<GreenTank*> enemies2;
        std::vector<YellowTank*> enemies3;
        std::vector<Projectile*> projectiles;
        std::pair<double, double> playerStart;
        PlayerAI* playerAI;
        int transparency = 0;
        int titlePos = 0;

    public:
        Intro() {
            this->name = "INTRO";
            this->playerAI = new PlayerAI(Width * 0.1, Height * 0.8, Direction::UP, 1);
            this->layout.push_back(new Block(0, 0, Width * 2, 10));
            this->layout.push_back(new Block(0, 0, 10, Height * 2));
            this->layout.push_back(new Block(Width, 0, 10, Height * 2));
            this->layout.push_back(new Block(0, Height, Width * 2, 10));
            this->layout.push_back(new Block(Width * 0.25, Height * 2/3, 50, Height * 2/3));
            this->layout.push_back(new Block(Width * 0.5, Height / 3, 50, Height * 2/3));
            this->layout.push_back(new Block(Width * 0.75, Height * 0.6, Width * 0.25, Width * 0.25));

            this->enemies1.push_back(new BeigeTank(Width * 0.375, Height * 0.25, Direction::LEFT, 2));
            this->enemies2.push_back(new GreenTank(Width * 0.55, Height * 0.125, Direction::LEFT, 3));
            this->enemies2.push_back(new GreenTank(Width * 0.5, Height * 0.875, Direction::LEFT, 4));
            this->enemies3.push_back(new YellowTank(Width * 0.9, Height * 0.6, Direction::UP, 5));
        }

        virtual void Draw() override;
        virtual void Update() override;
        virtual void KeyPressed(int key) override;
        virtual void KeyReleased() override;
		virtual void MousePressed(int x, int y, int button) override;
        virtual void Reset() override;
        int getEnemyCount() { return this->enemies1.size() + this->enemies2.size() + this->enemies3.size(); }
        void manageAnimations();

        ~Intro() {}

};