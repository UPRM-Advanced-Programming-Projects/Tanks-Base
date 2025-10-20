#include "YellowTank.hpp"

void YellowTank::draw() {
    rlPushMatrix();
        rlTranslatef(X, Y, 0.0f);
        rlRotatef(this->angle, 0.0f, 0.0f, 1.0f);
        DrawTexturePro(ImageManager::tankBodies, this->body, 
                      (Rectangle){(float)(-this->width / 2), (float)(-this->length / 2), (float)this->width, (float)this->length}, 
                      (Vector2){0, 0}, 0, (Color){255, 255, 255, 255});
    rlPopMatrix();

    rlPushMatrix();
        rlTranslatef(X, Y, 0.0f);
        rlRotatef(this->aimAngle, 0.0f, 0.0f, 1.0f);
        DrawTexturePro(ImageManager::tankHeads, this->head, 
                      (Rectangle){-38.0f, -16.0f, 76.0f, 32.0f}, 
                      (Vector2){0, 0}, 0, (Color){255, 255, 255, 255});
    rlPopMatrix();
}

void YellowTank::update() {
    this->fireRate = std::max(this->fireRate - 1, 0);
    this->hitBox.setPosition(X, Y);

    if (!this->hasTarget)  {
        this->makeTurnTimer--;
        this->targetAngle = angle;

        if (turnTimer > 0) {
            this->angle += (total / 45) * turnDir;
            turnTimer -= total / 45;
        }
    }
    
    if (this->makeTurnTimer <= 0) {
        if (this->turnTimer <= 0) {
            turnDir = Math::sign(dist(gen));
            turnTimer = (turnDir > 0) ? (90 - fmod(this->angle, 90)) : fmod(this->angle, 90);
            total = turnTimer;
            makeTurnTimer = GetRandomValue(180, 420);

        } else {
            makeTurnTimer = GetRandomValue(180, 300);
        }
    }

    for (int i = 0; i < sightline.hitboxes.size(); i++) {
        double dist = sightline.distances[i];
        sightline.hitboxes[i].setPosition(X + dist * cos(this->aimAngle * PI/180), Y + dist * sin(this->aimAngle * PI/180));
    }

    double angleDiff = Math::getAngleDif(this->aimAngle, this->targetAngle);

    this->aimAngle -= this->hasTarget ? angleDiff / 5 : angleDiff / 25;
    if (this->aimAngle > 360.0) this->aimAngle -= 360.0;
    if (this->aimAngle <   0.0) this->aimAngle += 360.0;
    if (this->angle > 360.0) this->angle -= 360.0;
    if (this->angle <   0.0) this->angle += 360.0;

}

void YellowTank::shoot(std::vector<Projectile*> &projectiles, std::pair<double, double> target) {
    if (fireRate <= 0 && this->hasTarget) {
        PlaySound(SoundManager::shoot);
        Missile* m = new Missile(X, Y, 2, this->projectileSpeed, target, this->ID);
        projectiles.push_back(m);
        this->fireRate = maxFireRate;
    }
}

void YellowTank::targetSystem(CustomHitbox target, std::vector<Block*> blocks) {
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
            if (CustomHitbox::collision(b->getHitbox(), hb)) {
                hasTarget = false;
                return;
            }
        }
    }
}

void YellowTank::move(std::vector<Block*> &blocks) {
    if (this->moving && !IsSoundPlaying(SoundManager::moving)) PlaySound(SoundManager::moving); 
    this->collisionBox.setPosition(X, Y);
    this->velocity.first = cos(angle * PI / 180);
    this->velocity.second = sin(angle * PI / 180);
    
    if (turnTimer <= 0 && !this->hasTarget) {
        if (!this->blockCollision(blocks)) {
            this->moving = true;
            this->position.first += this->velocity.first * speed;
            this->position.second += this->velocity.second * speed;
        }

    } else {
        this->moving = false;
    }
    
}

void YellowTank::projectileCollision(std::vector<Projectile*> &projectiles) {
    for (Projectile* p : projectiles) {
        if (CustomHitbox::collision(this->hitBox, p->getHitbox()) && (p->ID != -1 && p->ID != this->ID)) {
            this->health--;
            ImageManager::animations.push_back(Animation(X, Y, 32, 32, 32, 32, 9, ImageManager::tankExplosion));
            ImageManager::animations.push_back(Animation(p->getPosition().first, p->getPosition().second,
                                                       57, 60, 30, 31, 6, ImageManager::projectileExplosion));
            p->del = true;
            PlaySound(SoundManager::enemyDeath);
        }
    }
}

bool YellowTank::blockCollision(std::vector<Block*> blocks) {
    for (Block* b : blocks) {
        if (CustomHitbox::collision(this->collisionBox, b->getHitbox())) {
            std::pair<double, double> collision = CustomHitbox::collisionMargins(this->collisionBox, b->getHitbox());
            if (abs(collision.second) < abs(collision.first)) {
                this->position.second += collision.second - Math::sign(this->velocity.second);
            } else {
                this->position.first += collision.first - Math::sign(this->velocity.first);
            }
            
            this->collisionBox.setPosition(X, Y);
            turnDir = Math::sign(dist(gen));
            turnTimer = (turnDir > 0) ? (90 - fmod(this->angle, 90)) : fmod(this->angle, 90);
            total = turnTimer;
            return true;
        }

    }
    
    return false;
}

void YellowTank::drawHitboxes() {
    this->hitBox.draw();
    this->collisionBox.draw();
    for (CustomHitbox c : sightline.hitboxes) { c.draw(); }
}