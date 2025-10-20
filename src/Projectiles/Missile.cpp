#include "Missile.hpp"

void Missile::draw() {
    rlPushMatrix();
        rlTranslatef(this->position.first, this->position.second, 0.0f);
        rlRotatef(this->angle, 0.0f, 0.0f, 1.0f);
        DrawTexturePro(ImageManager::projectileSprites, (Rectangle){0, 0, 21, 20}, (Rectangle){-4, -4, 8, 8}, (Vector2){0, 0}, 0, (Color){255, 255, 255, 255});
    rlPopMatrix();

    //this->hitbox.draw();
}

void Missile::update(std::vector<Block*> blocks, CustomHitbox target) {
    this->position.first += this->velocity.first * this->speed;
    this->position.second += this->velocity.second * this->speed;
    this->hitbox.setPosition(position.first, position.second);
    
    for (Block* b : blocks) {
        if (CustomHitbox::collision(this->getHitbox(), b->getHitbox())) {
            std::pair<double, double> margin = CustomHitbox::collisionMargins(this->getHitbox(), b->getHitbox());
            if (abs(margin.first) > abs(margin.second)) {
                PlaySound(SoundManager::bounce);
                this->bounceY();
            } else {
                PlaySound(SoundManager::bounce);
                this->bounceX();
            }
        }
    }

    if (this->ricochet < 0) { 
        this->del = true; 
        PlaySound(SoundManager::enemyDeath);
        ImageManager::animations.push_back(Animation(this->position.first, this->position.second,
                                                   57, 60, 30, 31, 6, ImageManager::projectileExplosion));
    }

}

void Missile::bounceX() { 
    if (this->velocity.first < 0) {
        Vector2 bounceVelocity = reflect((Vector2){ (float)this->velocity.first, (float)this->velocity.second }, (Vector2){ 1, 0 });
        velocity = std::pair<double, double> { bounceVelocity.x, bounceVelocity.y };
    }
    else if (this->velocity.first > 0) {
        Vector2 bounceVelocity = reflect((Vector2){ (float)this->velocity.first, (float)this->velocity.second }, (Vector2){ -1, 0 });
        velocity = std::pair<double, double> { bounceVelocity.x, bounceVelocity.y };
    }
    this->ricochet--;
    this->angle = RAD2DEG * atan2f(this->velocity.second, this->velocity.first);
}

void Missile::bounceY() { 
    if (this->velocity.second < 0) {
        Vector2 bounceVelocity = reflect((Vector2){ (float)this->velocity.first, (float)this->velocity.second }, (Vector2){ 0, -1 });
        velocity = std::pair<double, double> { bounceVelocity.x, bounceVelocity.y };
    }
    else if (this->velocity.second > 0) {
        Vector2 bounceVelocity = reflect((Vector2){ (float)this->velocity.first, (float)this->velocity.second }, (Vector2){ 0, 1 });
        velocity = std::pair<double, double> { bounceVelocity.x, bounceVelocity.y };
    } 
    this->ricochet--;
    this->angle = RAD2DEG * atan2f(this->velocity.second, this->velocity.first);
}

Vector2 Missile::reflect(Vector2 v, Vector2 n) {
    n = Vector2Normalize(n);
    float dot = Vector2DotProduct(v, n);
    return Vector2Subtract(v, Vector2Scale(n, 2.0f * dot));
}