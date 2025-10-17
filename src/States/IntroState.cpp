#pragma once
#include "IntroState.hpp"

void Intro::Draw() {
    if (this->playerAI != nullptr) this->playerAI->draw();
    for (Enemy* e : this->enemies) e->draw();
    for (Block* b : this->layout) b->draw();
    for (Animation a : Tank::animations) a.draw();
    for (Animation a : Projectile::animations) a.draw();
    for (Projectile* p : this->projectiles) p->draw();
    DrawRectangle(0, 0, Width, Height, (Color){0, 0, 0, (unsigned char)transparency});
    DrawText("Tanks!", titlePos, Height / 5, 128, (Color){255, 255, 255, 255});
    titlePos = std::min(2 * titlePos + 1, Width / 2 - (65 * 3));
    DrawText("Press Enter to Start", Width / 2 - (16 * 5), Height * 0.4, 16, (Color){255, 255, 255, 255});
}

void Intro::Update() {
    if (!IsSoundPlaying(SoundManager::introTheme)) PlaySound(SoundManager::introTheme);
    for (Animation& a : Tank::animations) a.update();
    for (Animation& a : Projectile::animations) a.update();
    manageAnimations();
    Enemy::allyCollision(this->enemies);
    
    this->enemies.erase(remove_if(this->enemies.begin(), this->enemies.end(), [](Enemy* e) {
        return e->getHealth() <= 0;
    }), this->enemies.end());
    
    if (this->playerAI != nullptr) {
        for (Enemy* e : this->enemies) {
            e->updateAll(this->playerAI, this->projectiles, this->layout);
            e->projectileCollision(this->projectiles);
        }
        
        for (Projectile* &p : this->projectiles) {
            p->update(this->layout, this->playerAI->getHitbox());
        }
    
        Enemy* target = nullptr;
        for (Enemy* e : this->enemies) {
            this->playerAI->targetSystem(e->getHitbox(), this->layout);
            if (this->playerAI->getHasTarget()) {
                target = e;
                break;
            }
        }

        this->playerAI->update();
        this->playerAI->move(this->layout);
        this->playerAI->entityCollision(this->enemies);
        this->playerAI->projectileCollision(this->projectiles);
    
        if (target != nullptr) {
            this->playerAI->targetSystem(target->getHitbox(), this->layout);
            this->playerAI->shoot(projectiles, target);
            this->playerAI->trackTarget(target->getHitbox(), this->layout);
        }

        if (this->playerAI->getHealth() <= 0) this->playerAI = nullptr;
    }

    Projectile::cleanProjectiles(this->projectiles);
    Projectile::projectileCollision(this->projectiles);

    if (playerAI == nullptr || this->enemies.size() <= 0) transparency += 4;
    if (transparency >= 255) {
        Reset();
        transparency = 0;
    }
}

void Intro::KeyPressed(int key) {
    if (key == KEY_ENTER) {
        this->done = true;
    }
}

void Intro::KeyReleased() {

}

void Intro::MousePressed(int x, int y, int button) {

}

void Intro::Reset() {
    this->playerAI = new PlayerAI(Width * 0.1, Height * 0.8, Direction::UP, 1);
    this->enemies.clear();
    this->projectiles.clear();
    this->enemies.push_back(new GreenTank(Width * 0.5, Height * 0.125, Direction::LEFT, 2));
    this->enemies.push_back(new GreenTank(Width * 0.5, Height * 0.875, Direction::LEFT, 3));
    this->enemies.push_back(new BeigeTank(Width * 0.375, Height * 0.25, Direction::LEFT, 4));
    this->enemies.push_back(new YellowTank(Width * 0.9, Height * 0.6, Direction::UP, 5));
    transparency = 0;
}

void Intro::manageAnimations() {
    Tank::animations.erase(remove_if(Tank::animations.begin(), Tank::animations.end(), [](Animation& a) {
        return a.done;
    }), Tank::animations.end());

    Projectile::animations.erase(remove_if(Projectile::animations.begin(), Projectile::animations.end(), [](Animation& a) {
        return a.done;
    }), Projectile::animations.end());
}