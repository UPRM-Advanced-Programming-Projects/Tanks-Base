#include "Sightline.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

SightLine makeSightline(std::vector<double> distances, std::vector<double> sizes) {
    std::vector<CustomHitbox> hitboxes;
    for (double size : sizes) {
        hitboxes.push_back(CustomHitbox(0, 0, size, size));
    }

    return (SightLine){
        hitboxes,
        distances
    };
}