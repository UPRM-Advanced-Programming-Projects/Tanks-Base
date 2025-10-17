#pragma once
#include <iostream>
#include "SoundManager.hpp"

class State {
    protected:
        std::string name;
        
    public:
        bool done = false;
        
        virtual void Draw() = 0;
        virtual void Update() = 0;
        virtual void KeyPressed(int key) = 0;
        virtual void KeyReleased() = 0;
		virtual void MousePressed(int x, int y, int button) = 0;
        virtual void Reset() = 0;

};