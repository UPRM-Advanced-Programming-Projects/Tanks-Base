#pragma once
#include "IntroState.hpp"

void Intro::Draw() {
    if (this->playerAI != nullptr) this->playerAI->draw();
    for (BeigeTank* e : this->enemies1) { e->draw(); }
    for (GreenTank* e : this->enemies2) { e->draw(); }
    for (YellowTank* e : this->enemies3) { e->draw(); }
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
    
    this->enemies1.erase(remove_if(this->enemies1.begin(), this->enemies1.end(), [](BeigeTank* e) {
        return e->getHealth() <= 0;
    }), this->enemies1.end());

    this->enemies2.erase(remove_if(this->enemies2.begin(), this->enemies2.end(), [](GreenTank* e) {
        return e->getHealth() <= 0;
    }), this->enemies2.end());

    this->enemies3.erase(remove_if(this->enemies3.begin(), this->enemies3.end(), [](YellowTank* e) {
        return e->getHealth() <= 0;
    }), this->enemies3.end());

    
    if (this->playerAI != nullptr) {
        for (BeigeTank* e : this->enemies1) {
            e->update();
            e->targetSystem(playerAI->getHitbox(), this->layout);
            e->shoot(projectiles, playerAI->getPosition());
            e->projectileCollision(projectiles);
        }
        for (GreenTank* e : this->enemies2) {
            e->update();
            e->targetSystem(playerAI->getHitbox(), this->layout);
            e->move(this->layout);
            e->shoot(projectiles, playerAI->getPosition());
            e->projectileCollision(projectiles);
        }
        for (YellowTank* e : this->enemies3) {
            e->update();
            e->targetSystem(playerAI->getHitbox(), this->layout);
            e->move(this->layout);
            e->shoot(projectiles, playerAI->getPosition());
            e->projectileCollision(projectiles);
        }
        
        for (Projectile* &p : this->projectiles) {
            p->update(this->layout, this->playerAI->getHitbox());
        }
    
        BeigeTank* targetB = nullptr;
        for (BeigeTank* e : this->enemies1) {
            this->playerAI->targetSystem(e->getHitbox(), this->layout);
            if (this->playerAI->getHasTarget()) {
                targetB = e;
                break;
            }
        }
        GreenTank* targetG = nullptr;
        for (GreenTank* e : this->enemies2) {
            this->playerAI->targetSystem(e->getHitbox(), this->layout);
            if (this->playerAI->getHasTarget()) {
                targetG = e;
                break;
            }
        }
        YellowTank* targetY = nullptr;
        for (YellowTank* e : this->enemies3) {
            this->playerAI->targetSystem(e->getHitbox(), this->layout);
            if (this->playerAI->getHasTarget()) {
                targetY = e;
                break;
            }
        }

        this->playerAI->update();
        this->playerAI->move(this->layout);
        this->playerAI->projectileCollision(this->projectiles);
    
        if (targetB != nullptr) {
            this->playerAI->targetSystem(targetB->getHitbox(), this->layout);
            this->playerAI->shoot(projectiles, targetB->getPosition(), targetB->getVelocity(), targetB->getSpeed(), targetB->isMoving());
            this->playerAI->trackTarget(targetB->getHitbox(), this->layout);
        }

        if (targetG != nullptr) {
            this->playerAI->targetSystem(targetG->getHitbox(), this->layout);
            this->playerAI->shoot(projectiles, targetG->getPosition(), targetG->getVelocity(), targetG->getSpeed(), targetG->isMoving());
            this->playerAI->trackTarget(targetG->getHitbox(), this->layout);
        }

        if (targetY != nullptr) {
            this->playerAI->targetSystem(targetY->getHitbox(), this->layout);
            this->playerAI->shoot(projectiles, targetY->getPosition(), targetY->getVelocity(), targetY->getSpeed(), targetY->isMoving());
            this->playerAI->trackTarget(targetY->getHitbox(), this->layout);
        }

        if (this->playerAI->getHealth() <= 0) this->playerAI = nullptr;
    }

    Projectile::cleanProjectiles(this->projectiles);
    Projectile::projectileCollision(this->projectiles);

    if (playerAI == nullptr || this->getEnemyCount() <= 0) transparency += 4;
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
    this->enemies1.clear();
    this->enemies2.clear();
    this->enemies3.clear();
    this->projectiles.clear();
    this->enemies1.push_back(new BeigeTank(Width * 0.375, Height * 0.25, Direction::LEFT, 2));
    this->enemies2.push_back(new GreenTank(Width * 0.55, Height * 0.125, Direction::LEFT, 3));
    this->enemies2.push_back(new GreenTank(Width * 0.5, Height * 0.875, Direction::LEFT, 4));
    this->enemies3.push_back(new YellowTank(Width * 0.9, Height * 0.6, Direction::UP, 5));
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