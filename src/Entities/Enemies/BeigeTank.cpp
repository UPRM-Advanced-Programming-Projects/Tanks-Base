#include "BeigeTank.hpp"

void BeigeTank::draw() {
    rlPushMatrix();
        rlTranslatef(X, Y, 0.0f);
        rlRotatef(this->angle, 0.0f, 0.0f, 1.0f);
        DrawTexturePro(Tank::tankBodies, this->body, 
                      (Rectangle){(float)(-this->width / 2), (float)(-this->length / 2), (float)this->width, (float)this->length}, 
                      (Vector2){0, 0}, 0, (Color){255, 255, 255, 255});
    rlPopMatrix();

    rlPushMatrix();
        rlTranslatef(X, Y, 0.0f);
        rlRotatef(this->aimAngle, 0.0f, 0.0f, 1.0f);
        DrawTexturePro(Tank::tankHeads, this->head, 
                      (Rectangle){-38.0f, -16.0f, 76.0f, 32.0f}, 
                      (Vector2){0, 0}, 0, (Color){255, 255, 255, 255});
    rlPopMatrix();
}

void BeigeTank::update() {
    this->fireRate = std::max(this->fireRate - 1, 0);
    this->collisionBox.setPosition(X, Y);
    this->hitBox.setPosition(X, Y);

    for (int i = 0; i < sightline.hitboxes.size(); i++) {
        double dist = sightline.distances[i];
        sightline.hitboxes[i].setPosition(X + dist * cos(this->aimAngle * PI/180), 
                                            Y + dist * sin(this->aimAngle * PI/180));
    }

    double angleDiff = Math::getAngleDif(this->aimAngle, this->targetAngle);
    if (!this->hasTarget) { this->targetAngle += 0.5; }

    this->aimAngle -= this->hasTarget ? angleDiff / 5 : angleDiff / 25;
    if (this->aimAngle > 360.0) this->aimAngle -= 360.0;
    if (this->aimAngle <   0.0) this->aimAngle += 360.0;

}

void BeigeTank::shoot(std::vector<Projectile*> &projectiles, std::pair<double, double> target) {
    if (fireRate <= 0 && this->hasTarget) {
        PlaySound(SoundManager::shoot);
        Missile* m = new Missile(X, Y, 2, this->projectileSpeed, target, this->ID);
        projectiles.push_back(m);
        this->fireRate = maxFireRate;
    }
}

void BeigeTank::targetSystem(CustomHitbox target, std::vector<Block*> blocks) {
    bool didCollide = false;
    for (int i = 0; i < sightline.hitboxes.size(); i++) {
        if (CustomHitbox::collision(sightline.hitboxes[i], target)) {
            didCollide = true;
            break;
        }
    }

    if (!didCollide) {
        hasTarget = false;
        return;
    }

    CustomHitbox hb = CustomHitbox(X, Y, 2, 2);
    double ang = Math::atan3(target.box.y - Y, target.box.x - X);
    double offSetX = cos((PI/180)*ang);
    double offSetY = sin((PI/180)*ang);
    
    while (true) {
        hb.setPosition(hb.box.x + offSetX, hb.box.y + offSetY);
        if (CustomHitbox::collision(target, hb)) {
            hasTarget = true;
            this->targetAngle = ang;
            return;
        }

        for (Block* b : blocks) {
            if (CustomHitbox::collision(b->getHitbox(), hb) && !(b->IsWindow())) {
                hasTarget = false;
                return;
            }
        }
    }
}

void BeigeTank::projectileCollision(std::vector<Projectile*> &projectiles) {
    for (Projectile* p : projectiles) {
        if (CustomHitbox::collision(this->hitBox, p->getHitbox()) && (p->ID != -1 && p->ID != this->ID)) {
            this->health--;
            Tank::animations.push_back(Animation(X, Y, 32, 32, 32, 32, 9, Tank::tankExplosion));
            Projectile::animations.push_back(Animation(p->getPosition().first, p->getPosition().second,
                                                       57, 60, 30, 31, 6, Projectile::projectileExplosion));
            p->del = true;
            PlaySound(SoundManager::enemyDeath);
        }
    }
}

void BeigeTank::drawHitboxes() {
    this->hitBox.draw();
    this->collisionBox.draw();
    for (CustomHitbox c : sightline.hitboxes) { c.draw(); }
}