#pragma once

#include "GameState.hpp"
#include "IntroState.hpp"
#include "GameOver.hpp"
#include "WinState.hpp"
#include "Transition.hpp"
class Program {
    public:
        Program();
        ~Program();

        void Update();
        void Draw();
        void Unload(); 

		void KeyPressed(int key);
		void KeyReleased();
		void MousePressed(int x, int y, int button);
        void Reset();
        
        std::string currentState = "INTRO";
        Counter* counter = new Counter();
        Intro introState = Intro();
        Game gameState = Game();
        GameOver gameOverState = GameOver();
        Win winState = Win();
        Transition transitionState = Transition();
        Texture2D ground;
};