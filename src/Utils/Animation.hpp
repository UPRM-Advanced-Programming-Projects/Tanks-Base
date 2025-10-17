#pragma once
#include <iostream>
#include "raylib.h"
#include "raylib-cpp-utils.hpp"

class Animation {
    private:
        int width, length, duration;
        int xSize, ySize;
        int frame = -1;
        double x, y;
        Texture2D Sheet;

    public:
        bool done = false;

        Animation(double x, double y, int width, int length, int xSize, int ySize, int duration, Texture2D sheet) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->length = length;
            this->xSize = xSize;
            this->ySize = ySize;
            this->duration = duration;
            this->Sheet = sheet;
        }

        void update();
        void draw();

        ~Animation() {}
};