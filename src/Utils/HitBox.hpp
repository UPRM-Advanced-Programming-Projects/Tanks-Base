#pragma once
#include <iostream>
#include "raylib-cpp.hpp"

class CustomHitbox {
    public:
        Rectangle box;
        static bool drawHitBox;

        CustomHitbox(double x, double y, double width, double length) {
            this->box = raylib::Rectangle(x, y, width, length);
        }

        CustomHitbox() {
            this->box = raylib::Rectangle(0, 0, 0, 0);
        }

        void setPosition(double x, double y) {
            this->box.x = x;
            this->box.y = y;
        }

        void setSize(double width, double length) {
            this->box.width = width;
            this->box.height = length;
        }

        double getWidth() { return this->box.width; }
        double getLength() { return this->box.height; }

        double left() { return this->box.x - this->box.width / 2; }
        double right() { return this->box.x + this->box.width / 2; }
        double top() { return this->box.y - this->box.height / 2; }
        double bottom() { return this->box.y + this->box.height / 2; }
        bool equals(CustomHitbox h);

        static bool collision(CustomHitbox b1, CustomHitbox b2);
        static std::pair<double, double> collisionMargins(CustomHitbox b1, CustomHitbox b2);

        void draw();

};