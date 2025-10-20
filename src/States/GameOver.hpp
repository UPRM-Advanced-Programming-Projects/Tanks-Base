#pragma once
#include "State.hpp"
#include "Map.hpp"

class GameOver : public State {
    private:
        int levelReached = 0;
        std::vector<Block*> layout;
        std::vector<Tank*> enemies;
        bool finished = false;
        bool start = true;
        int transparency = 0;
        double titlePos = 0;
    
    public:
        GameOver() {
            this->name = "GAMEOVER";
        }
        
        void setLevelReached(int level) { this->levelReached = level; }
        void setLevel(Map level) {
            this->layout = level.getLayout();
            this->enemies = level.enemies;
        }

        void Update() override;
        void Draw() override;
		void KeyPressed(int key) override;
		void KeyReleased() override;
		void MousePressed(int x, int y, int button) override;
        void Reset() override;

        ~GameOver() {}
};