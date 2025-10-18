#pragma once
#include "HitBox.hpp"
#include <random>

#define X this->position.first
#define Y this->position.second

extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<float> dist;

enum Direction {
    UP = 270,
    DOWN = 90, 
    LEFT = 180,
    RIGHT = 0
};

struct SightLine {
    std::vector<CustomHitbox> hitboxes;
    std::vector<double> distances;
};

SightLine makeSightline(std::vector<double> distances, std::vector<double> sizes);