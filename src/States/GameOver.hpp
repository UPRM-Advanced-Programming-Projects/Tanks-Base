#pragma once
#include "State.hpp"
#include "Map.hpp"

class GameOver : public State {
    private:
        int levelReached = 0;
        std::vector<Block*> layout;
        std::vector<BeigeTank*> enemies1;
        std::vector<GreenTank*> enemies2;
        std::vector<RedTank*> enemies3;
        std::vector<YellowTank*> enemies4;
        bool finished = false;
        bool start = true;
        int transparency = 0;
        double titlePos = 0;
    
    public:
        inline static Texture2D icons;

        GameOver() {
            this->name = "GAMEOVER";
        }
        
        void setLevelReached(int level) { this->levelReached = level; }
        void setLevel(Map level) {
            this->layout = level.getLayout();
            this->enemies1 = level.enemies1;
            this->enemies2 = level.enemies2;
            this->enemies3 = level.enemies3;
            this->enemies4 = level.enemies4;
        }

        void Update() override;
        void Draw() override;
		void KeyPressed(int key) override;
		void KeyReleased() override;
		void MousePressed(int x, int y, int button) override;
        void Reset() override;

        static void LoadImages() {
            icons = LoadTextureFromImage(LoadImage("images/TankIcons.png"));
        }

        static void UnloadImages() {
            UnloadTexture(icons);
        }

        ~GameOver() {}
};