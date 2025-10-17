#pragma once
#include <iostream>
#include "raylib.h"

class SoundManager {
    public:
        SoundManager() {}

        inline static Sound introTheme;
        inline static Sound startUp;
        inline static Sound theme;
        inline static Sound shoot;
        inline static Sound enemyDeath;
        inline static Sound playerDeath;
        inline static Sound bounce;
        inline static Sound gameOver;
        inline static Sound levelComplete;
        inline static Sound winTheme;
        inline static Sound moving;

        static void LoadSounds() {
            introTheme = LoadSound("audio/IntroTheme.mp3");
            startUp = LoadSound("audio/StartUp.mp3");
            theme = LoadSound("audio/Theme.mp3");
            shoot = LoadSound("audio/Shoot.wav");
            enemyDeath = LoadSound("audio/EnemyDeath.wav");
            playerDeath = LoadSound("audio/PlayerDeath.wav");
            bounce = LoadSound("audio/Bounce.wav");
            gameOver = LoadSound("audio/GameOver.mp3");
            levelComplete = LoadSound("audio/LevelComplete.mp3");
            winTheme = LoadSound("audio/WinTheme.mp3");
            moving = LoadSound("audio/Moving.wav");
        }

        static void UnloadSounds() {
            UnloadSound(introTheme);
            UnloadSound(startUp);
            UnloadSound(theme);
            UnloadSound(shoot);
            UnloadSound(enemyDeath);
            UnloadSound(playerDeath);
            UnloadSound(bounce);
            UnloadSound(gameOver);
            UnloadSound(levelComplete);
            UnloadSound(winTheme);
            UnloadSound(moving);
        }
};