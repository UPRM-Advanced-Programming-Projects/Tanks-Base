#pragma once
#include <iostream>
#include "raylib.h"
#include "Animation.hpp"

class ImageManager {
    public:
        ImageManager() {}

        inline static std::vector<Animation> animations;
        
        inline static Texture2D tankBodies;
        inline static Texture2D tankHeads;
        inline static Texture2D tankExplosion;
        inline static Texture2D projectileSprites;
        inline static Texture2D projectileExplosion;
        inline static Texture2D icons;

        static void LoadImages() {
            tankBodies = LoadTextureFromImage(LoadImage("images/TankBodies.png"));
            tankHeads = LoadTextureFromImage(LoadImage("images/TankHeads.png"));
            tankExplosion = LoadTextureFromImage(LoadImage("images/TankExplosion.png"));
            projectileSprites = LoadTextureFromImage(LoadImage("images/Projectiles.png"));
            projectileExplosion = LoadTextureFromImage(LoadImage("images/ProjectileExplosion.png"));
            icons = LoadTextureFromImage(LoadImage("images/TankIcons.png"));
        }

        static void UnloadImages() {
            UnloadTexture(tankBodies);
            UnloadTexture(tankHeads);
            UnloadTexture(tankExplosion);
            UnloadTexture(projectileSprites);
            UnloadTexture(projectileExplosion);
            UnloadTexture(icons);
        }
};