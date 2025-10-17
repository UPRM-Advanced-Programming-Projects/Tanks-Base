#include "Player.hpp"

#define PlayerX this->position.first
#define PlayerY this->position.second

void Player::draw() {
    Vector2 mouse = GetMousePosition();
    rlPushMatrix();
        rlTranslatef(PlayerX, PlayerY, 0.0f);
        rlRotatef(this->angle, 0.0f, 0.0f, 1.0f);
        DrawTexturePro(Tank::tankBodies, (Rectangle){2, 0, 64, 64}, 
                      (Rectangle){(float)(-this->width / 2), (float)(-this->length / 2), (float)this->width, (float)this->length}, 
                      (Vector2){0, 0}, 0, (Color){255, 255, 255, 255});
    rlPopMatrix();
    //this->hitBox.draw();

    rlPushMatrix();
        rlTranslatef(PlayerX, PlayerY, 0.0f);
        rlRotatef(this->aimAngle, 0.0f, 0.0f, 1.0f);
        DrawTexturePro(Tank::tankHeads, (Rectangle){0, 0, 153, 64}, 
                      (Rectangle){-38.0f, -16.0f, 76.0f, 32.0f}, 
                      (Vector2){0, 0}, 0, (Color){255, 255, 255, 255});
    rlPopMatrix();

    DrawRectangle(mouse.x - 12, mouse.y - 1, 24, 2, BLUE);
    DrawRectangle(mouse.x - 1, mouse.y - 12, 2, 24, BLUE);

}

void Player::update() {
    Vector2 mouse = GetMousePosition();
    this->fireRate = std::max(this->fireRate - 1, 0);
    this->aimAngle = Math::atan3((PlayerY - mouse.y), (PlayerX - mouse.x)) + 180;
    if (this->moving && !IsSoundPlaying(SoundManager::moving)) PlaySound(SoundManager::moving); 
}

void Player::shoot(std::vector<Projectile*> &projectiles) {
    if (fireRate <= 0) {
        PlaySound(SoundManager::shoot);
        Missile* m = new Missile(PlayerX + 38 * cos(this->aimAngle * DEG2RAD), PlayerY + 38 * sin(this->aimAngle * DEG2RAD), 2, 4.0, 0);
        projectiles.push_back(m);
        this->fireRate = 60;
    }
}

void Player::projectileCollision(std::vector<Projectile*> &projectiles) {
    for (Projectile* p : projectiles) {
        if (CustomHitbox::collision(this->hitBox, p->getHitbox())) {
            this->health--;
            this->lives--;
            PlaySound(SoundManager::playerDeath);
            Tank::animations.push_back(Animation(PlayerX, PlayerY, 32, 32, 32, 32, 9, Tank::tankExplosion));
            Projectile::animations.push_back(Animation(p->getPosition().first, p->getPosition().second,
                                                       57, 60, 30, 31, 6, Projectile::projectileExplosion));
            p->del = true;
        }

        Mine* m = dynamic_cast<Mine*>(p);
        if (m && CustomHitbox::collision(this->hitBox, m->collisionBox)) {
            this->health--;
            this->lives--;
            PlaySound(SoundManager::playerDeath);
            Tank::animations.push_back(Animation(PlayerX, PlayerY, 32, 32, 32, 32, 9, Tank::tankExplosion));
            p->del = true;
        }
    }
}

void Player::controls(std::vector<Block*> &border, std::vector<CustomHitbox> enemies) {
    if (this->rotateRight) { this->rotate(-1); }
    if (this->rotateLeft) { this->rotate(1); }

    this->velocity.first = cos(angle * PI / 180);
    this->velocity.second = sin(angle * PI / 180);
    if (this->moveForward && !this->moveBackward) { 
        this->move();
    }

    if (this->moveBackward && !this->moveForward) { 
        this->velocity.first *= -1;
        this->velocity.second *= -1;
        this->move();
    }

    this->hitBox.setPosition(PlayerX, PlayerY);

    for (Block* b : border) {
        if (CustomHitbox::collision(this->hitBox, b->getHitbox())) {
            std::pair<double, double> collision = CustomHitbox::collisionMargins(this->hitBox, b->getHitbox());
            if (abs(collision.second) < abs(collision.first)) {
                this->position.second += collision.second;
            } else {
                this->position.first += collision.first;
            }
        }
    }

    for (CustomHitbox e : enemies) {
        if (CustomHitbox::collision(e, this->hitBox)) {
            std::pair<double, double> collision = CustomHitbox::collisionMargins(this->hitBox, e);
            if (abs(collision.second) < abs(collision.first)) {
                this->position.second += collision.second;
            } else {
                this->position.first += collision.first;
            }
        }
    }

    this->hitBox.setPosition(PlayerX, PlayerY);
    if (this->moveBackward || this->moveForward) { 
        this->moving = true; 
    } else {
        this->moving = false;
    }
}