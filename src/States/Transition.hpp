#pragma once
#include "State.hpp"
#include "Map.hpp"

class Transition : public State {
    private:
        int levelReached = 0;
        std::vector<Block*> layout;
        Player* player;
        bool finished = false;
        bool start = true;
        int transparency = 0;
        int titlePos = 0;
    
    public:
        inline static Texture2D icons;

        Transition() {
            this->name = "TRANSITION";
        }
        
        void setLevel(Map level, Player* p) {
            this->layout = level.getLayout();
            this->player = p;
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

        ~Transition() {}
};