#pragma once
#include "HitBox.hpp"

class Block {
    protected:
        CustomHitbox hitbox;
        bool isWindow;

    public:
        Block(double x, double y, double width, double length) {
            this->hitbox = CustomHitbox(x, y, width, length);
            this->isWindow = false;
        }

        Block(double x, double y, double width, double length, bool isWindow) {
            this->hitbox = CustomHitbox(x, y, width, length);
            this->isWindow = isWindow;
        }

        Block(double x, double y) {
            this->hitbox = CustomHitbox(x, y, 50, 50);
        }

        Block() {
            this->hitbox = CustomHitbox(0, 0, 50, 50);
        }
        
        CustomHitbox getHitbox() { return hitbox; }
        bool IsWindow() { return isWindow; }

        void setPosition(double x, double y) { this->hitbox.setPosition(x, y); }
        void setSize(double w, double l) { this->hitbox.setSize(w, l); }


        void draw() {
            if (this->isWindow) {
                DrawRectangle(this->hitbox.left(), this->hitbox.top(), 
                              this->hitbox.getWidth(), this->hitbox.getLength(), (Color){200, 200, 200, 128});
            } else {
                DrawRectangle(this->hitbox.left(), this->hitbox.top(), 
                              this->hitbox.getWidth(), this->hitbox.getLength(), (Color){0, 0, 0, 255});
            }
        }

        ~Block() {}
};