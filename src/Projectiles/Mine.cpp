#include "Mine.hpp"

void Mine::draw() {
    DrawTexturePro(projectileSprites, (Rectangle){48, 0, 21, 20}, 
                   (Rectangle){(float)this->position.first - 10, (float)this->position.second - 10, 20, 20}, 
                   (Vector2){0, 0}, 0, (Color){(unsigned char)color, (unsigned char)color, (unsigned char)color, 255});

    // this->hitbox.draw();
    // this->collisionBox.draw();
}

void Mine::update(std::vector<Block*> blocks, CustomHitbox target) {
    this->timer--;
    if (timer <= 0) {
        this->timer = 90;
        this->color += this->mult * 100;
        this->mult *= -1;
    }

    if (CustomHitbox::collision(target, this->collisionBox)) {
        Projectile::animations.push_back(Animation(this->position.first, this->position.second,
                                                   57, 60, 110, 110, 6, Projectile::projectileExplosion));
    }
}

