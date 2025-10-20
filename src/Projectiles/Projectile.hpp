#pragma once
#include "raylib-cpp.hpp"
#include "Block.hpp"
#include "MathUtils.hpp"
#include <vector>
#include <utility>
#include <cmath>
#include "SoundManager.hpp"
#include "ImageManager.hpp"

class Projectile {
    protected:
        std::pair<double, double> position;
        int ricochet;
        CustomHitbox hitbox;
        
    public:
        int ID;
        bool del;
        
        Projectile(double x, double y, int ricochet) {
            this->position.first = x;
            this->position.second = y;
            this->ricochet = ricochet;
            this->del = false;
            this->hitbox = CustomHitbox();
        }

        CustomHitbox getHitbox() { return hitbox; }
        std::pair<double, double> getPosition() { return this->position; }
        
        virtual void update(std::vector<Block*> blocks, CustomHitbox target) = 0;
        virtual void draw() = 0;

        static void cleanProjectiles(std::vector<Projectile*> &projectiles) {
            projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
                [](Projectile* p) {
                    if (!p->del) { return false; }
                    delete p; 
                    return true;
                }),
                projectiles.end()
            );
        }

        static void projectileCollision(std::vector<Projectile*> &projectiles) {
            for (int i = 0; i < projectiles.size(); i++) {
                for (int j = i + 1; j < projectiles.size(); j++) {
                    if (CustomHitbox::collision(projectiles[i]->getHitbox(), projectiles[j]->getHitbox())) {
                        PlaySound(SoundManager::enemyDeath);
                        projectiles[i]->del = true;
                        projectiles[j]->del = true;
                        ImageManager::animations.push_back(Animation(projectiles[i]->position.first, projectiles[i]->position.second,
                                                                   57, 60, 30, 31, 6, ImageManager::projectileExplosion));
                        ImageManager::animations.push_back(Animation(projectiles[j]->position.first, projectiles[j]->position.second,
                                                                   57, 60, 30, 31, 6, ImageManager::projectileExplosion));
                    }
                }
            }
        }

        virtual ~Projectile() {}
};