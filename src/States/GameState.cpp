#pragma once
#include "GameState.hpp"
#include "Transition.hpp"

bool isPaused = false;
int doFrames = 0;

void Game::Update() {
    for (Animation& a : Tank::animations) a.update();
    for (Animation& a : Projectile::animations) a.update();
    manageAnimations();

    if (startUp && !IsSoundPlaying(SoundManager::startUp)) PlaySound(SoundManager::startUp);
    if (!startUp && !IsSoundPlaying(SoundManager::theme)) PlaySound(SoundManager::theme);

    if ((isPaused && doFrames <= 0) || delay > 0) {
        delay--;
        return;
    } else {
        startUp = false;
        doFrames--;
    }

    world.update(player, projectiles);

    if (player->getHealth() <= 0 && player->lives <= 0) {
        this->done = true;
    } else if (player->getHealth() <= 0 && player->lives > 0) {
        player->setPosition(world.getX(), world.getY());
        player->setDirection(world.getAngle());
        player->setHealth(1);
        projectiles.clear();
        delay = 100;
        startUp = true;
    }

    if (world.getEnemies().size() <= 0 && Tank::animations.size() <= 0 && this->currentMap < 30) {
        this->nextLevel = true;
        this->startUp = true;
        this->delay = 90;
    }
    if (world.getEnemies().size() <= 0 && Tank::animations.size() <= 0 && this->currentMap == 30) this->win = true;
}

void Game::Draw() {
    for (Animation a : Tank::animations) a.draw();
    for (Animation a : Projectile::animations) a.draw();
    for (Projectile* &p : projectiles) { p->draw(); }
    player->draw();
    world.draw();

    for (int i = 0; i < player->lives; i++) {
        DrawTexturePro(Transition::icons, (Rectangle){0, 144, 36, 16},
                       (Rectangle){(66.0f * i), 0, 66, 29.3333}, (Vector2){0, 0}, 0,
                       (Color){255, 255, 255, 255});
    }
}

void Game::KeyPressed(int key) {
    if (key == 'A') { player->rotateRight = true; }
    if (key == 'D') { player->rotateLeft = true; }
    if (key == 'W' && !player->moveBackward) { player->moveForward = true; }
    if (key == 'S' && !player->moveForward) { player->moveBackward = true; }
    if (key == 'M') { world.showHitboxes = !world.showHitboxes; }
    if (key == 'J') { doFrames = 1; }
    if (key == ' ') { 
        isPaused = !isPaused; 
        player->rotateRight = false;
        player->rotateLeft = false;
        player->moveForward = false;
        player->moveBackward = false;
    }

    if (key == KEY_LEFT) { 
        currentMap = std::max(currentMap - 1, 1); 
        Reset();
    }

    if (key == KEY_RIGHT) { 
        currentMap = std::min(currentMap + 1, 30);
        Reset();
    }
}

void Game::KeyReleased() {
    if (!IsKeyDown('A')) { player->rotateRight = false; }
    if (!IsKeyDown('D')) { player->rotateLeft = false; }
    if (!IsKeyDown('W')) { player->moveForward = false; }
    if (!IsKeyDown('S')) { player->moveBackward = false; }
}

void Game::MousePressed(int x, int y, int button) {
    if (isPaused || delay > 0) return;
    if (IsMouseButtonPressed(button)) { player->shoot(projectiles); }
}

void Game::Reset() {
    world = Map::getMap(currentMap);
    player->setPosition(world.getX(), world.getY());
    player->setDirection(world.getAngle());
    projectiles.clear();
}

void Game::manageAnimations() {
    Tank::animations.erase(remove_if(Tank::animations.begin(), Tank::animations.end(), [](Animation& a) {
        return a.done;
    }), Tank::animations.end());

    Projectile::animations.erase(remove_if(Projectile::animations.begin(), Projectile::animations.end(), [](Animation& a) {
        return a.done;
    }), Projectile::animations.end());
}