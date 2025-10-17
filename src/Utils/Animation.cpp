#include "Animation.hpp"

void Animation::update() {
    this->frame++;
    if (this->frame > duration) {
        this->done = true;
    }
}

void Animation::draw() {
    DrawTexturePro(this->Sheet, (Rectangle){(float)(this->width * frame), 0, (float)this->width, (float)this->length}, 
                   (Rectangle){(float)(this->x - this->xSize / 2), (float)(this->y - this->ySize / 2), (float)this->xSize, (float)this->ySize}, 
                   (Vector2){0, 0}, 0, (Color){255, 255, 255, 255});
}