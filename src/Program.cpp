#include "Program.hpp"

Program::Program() {
    gameState.setCounter(counter);
    ground = LoadTextureFromImage(LoadImage("images/Ground.jpg"));
}

void Program::Update() {
    if (currentState == "INTRO") {
        introState.Update();
        if (introState.done) {
            currentState = "GAME";
            StopSound(SoundManager::introTheme);
        }
    } else if (currentState == "GAME") {
        gameState.Update();
        if (gameState.done) {
            currentState = "GAMEOVER";
            gameOverState.setLevel(gameState.world);
            gameOverState.setLevelReached(gameState.currentMap);
            gameOverState.setCounter(counter);
            StopSound(SoundManager::theme);
            StopSound(SoundManager::startUp);
        }
        if (gameState.win) {
            currentState = "WIN";
            winState.setLevel(gameState.world, gameState.player);
            winState.setCounter(counter);
            StopSound(SoundManager::theme);
            StopSound(SoundManager::startUp);
        }
        if (gameState.nextLevel) {
            currentState = "TRANSITION";
            transitionState.setLevel(gameState.world, gameState.player);
            transitionState.setCounter(counter);
            StopSound(SoundManager::theme);
            StopSound(SoundManager::startUp);
        }
    } else if (currentState == "GAMEOVER") {
        gameOverState.Update();
        if (gameOverState.done) {
            Reset();
            StopSound(SoundManager::gameOver);
        }
    } else if (currentState == "WIN") {
        winState.Update();
        if (winState.done) {
            Reset();
            StopSound(SoundManager::winTheme);
        }
    } else if (currentState == "TRANSITION") {
        transitionState.Update();
        if (transitionState.done) {
            currentState = "GAME";
            gameState.nextLevel = false;
            gameState.currentMap++;
            gameState.world = Map::getMap(gameState.currentMap);
            gameState.player->setPosition(gameState.world.getX(), gameState.world.getY());
            gameState.player->setDirection(gameState.world.getAngle());
            gameState.projectiles.clear();
            transitionState = Transition();
            StopSound(SoundManager::levelComplete);
        }
    }
}

void Program::Draw() {
    DrawTexture(ground, 0, 0, (Color){100, 100, 100, 255});

    if (currentState == "INTRO") {
        introState.Draw();
    } else if (currentState == "GAME") {
        gameState.Draw();
    } else if (currentState == "GAMEOVER") {
        gameOverState.Draw();
    } else if (currentState == "WIN") {
        winState.Draw();
    } else if (currentState == "TRANSITION") {
        transitionState.Draw();
    }
}

void Program::KeyPressed(int key) {
    if (currentState == "INTRO") {
        introState.KeyPressed(key);
    } else if (currentState == "GAME") {
        gameState.KeyPressed(key);
    } else if (currentState == "GAMEOVER") {
        gameOverState.KeyPressed(key);
    } else if (currentState == "WIN") {
        winState.KeyPressed(key);
    } else if (currentState == "TRANSITION") {
        transitionState.KeyPressed(key);
    }
}

void Program::KeyReleased() {
    if (currentState == "INTRO") {
        introState.KeyReleased();
    } else if (currentState == "GAME") {
        gameState.KeyReleased();
    } else if (currentState == "GAMEOVER") {
        gameOverState.KeyReleased();
    } else if (currentState == "WIN") {
        winState.KeyReleased();
    } else if (currentState == "TRANSITION") {
        transitionState.KeyReleased();
    }
}

void Program::MousePressed(int x, int y, int button) {
    if (currentState == "INTRO") {
        introState.MousePressed(x, y, button);
    } else if (currentState == "GAME") {
        gameState.MousePressed(x, y, button);
    } else if (currentState == "GAMEOVER") {
        gameOverState.MousePressed(x, y, button);
    } else if (currentState == "WIN") {
        winState.MousePressed(x, y, button);
    } else if (currentState == "TRANSITION") {
        transitionState.MousePressed(x, y, button);
    }
}

void Program::Reset() {
    currentState = "INTRO";
    introState = Intro();
    gameState = Game();
    gameOverState = GameOver();
    winState = Win();
    transitionState = Transition();
    counter = new Counter();
    gameState.setCounter(counter);
}

void Program::Unload() {

}

Program::~Program() {
    Unload();
}