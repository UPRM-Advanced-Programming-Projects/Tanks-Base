#include "HomingMissile.hpp"

void HomingMissile::draw() {
    rlPushMatrix();
        rlTranslatef(this->position.first, this->position.second, 0.0f);
        rlRotatef(this->angle, 0.0f, 0.0f, 1.0f);
        DrawTexturePro(projectileSprites, (Rectangle){24, 0, 21, 20}, (Rectangle){-4, -4, 8, 8}, (Vector2){0, 0}, 0, (Color){255, 255, 255, 255});
    rlPopMatrix();

    //this->hitbox.draw();
}

void HomingMissile::update(std::vector<Block*> blocks, CustomHitbox target) {
    this->position.first += this->velocity.first * this->speed;
    this->position.second += this->velocity.second * this->speed;
    this->hitbox.setPosition(position.first, position.second);
    this->chaseTarget(std::pair<double, double>({target.box.x, target.box.y}));

    for (Block* b : blocks) {
        if (!b->IsWindow() && CustomHitbox::collision(this->getHitbox(), b->getHitbox())) {
            this->del = true;
            Projectile::animations.push_back(Animation(this->position.first, this->position.second,
                                                       57, 60, 30, 31, 6, Projectile::projectileExplosion));
        }
    }
}

void HomingMissile::chaseTarget(std::pair<double, double> targetPos) {
    this->targetAngle =  Math::atan3(targetPos.second - this->position.second, targetPos.first - this->position.first);
    double angleDiff = Math::getAngleDif(this->angle, this->targetAngle);

    this->angle -= (angleDiff >= 0) ? 1.5 : -1.5;
    if (this->angle > 360.0) this->angle -= 360.0;
    if (this->angle <   0.0) this->angle += 360.0;

    this->velocity.first = cos(angle * PI / 180);
    this->velocity.second = sin(angle * PI / 180);
}