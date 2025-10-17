#include "Map.hpp"

void Map::draw() {
    for (Enemy* e : this->enemies) {
        e->draw();
        if (showHitboxes) e->drawHitboxes();
    }

    for (Block* b : this->layout) b->draw();
}
        
void Map::update(Player* &player, std::vector<Projectile*> &projectiles, Counter* &counter) {
    Enemy::allyCollision(this->enemies);

    for (Enemy* e : enemies) {
        if (e->getHealth() <= 0) {
                counter->update(e->colorID);
        }
    } 

    this->enemies.erase(remove_if(this->enemies.begin(), this->enemies.end(), [&counter](Enemy* e) {
        return e->getHealth() <= 0;
    }), this->enemies.end());
    
    for (Enemy* e : this->enemies) {
        e->updateAll(player, projectiles, this->layout);
        e->projectileCollision(projectiles);
    }
    
    for (Projectile* &p : projectiles) {
        p->update(this->layout, player->getHitbox());
    }
    
    player->update();
    player->controls(this->layout, this->getEnemyHitboxes());
    player->projectileCollision(projectiles);
    Projectile::cleanProjectiles(projectiles);
    Projectile::projectileCollision(projectiles);
    enemyCollisions();

}

void Map::enemyCollisions() {
    for (int i = 0; i < this->enemies.size(); i++) {
        for (int j = i + 1; j < this->enemies.size(); j++) {
            if (CustomHitbox::collision(enemies[i]->getHitbox(), enemies[j]->getHitbox())) {
                std::pair<double, double> collision = CustomHitbox::collisionMargins(enemies[i]->getHitbox(), enemies[j]->getHitbox());
                if (abs(collision.second) < abs(collision.first)) {
                    enemies[i]->setPosition(enemies[i]->getPosition().first, 
                    enemies[i]->getPosition().second + collision.second - Math::sign(enemies[i]->getVelocity().second));
                } else {
                    enemies[i]->setPosition(enemies[i]->getPosition().first + collision.first - Math::sign(enemies[i]->getVelocity().first),
                    enemies[i]->getPosition().second);
                }
                
            }
        }
    }
}

Map Map::getMap(int level) {
    Map map;
    double offset;

    switch (level){
        case 1:
            map = Map(Width / 2, Height / 3, Direction::DOWN);
            map.addBlock(new Block(Width / 2, Height / 2, Width / 2, 50));

            map.addEnemy(new BeigeTank(Width / 2, Height * 2/3, Direction::UP, Map::ID++));

            // map.addBlock(new Block(200, 200, 100, 100, true));
            // map.addEnemy(new BlackTank(100, 100, 90));
            break;

        case 2:
            map = Map(Width / 4, Height / 2, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.4833 + 25, Height * 0.25 + 25, Width / 6, 50));
            map.addBlock(new Block(Width * 0.4833 + 25, Height * 0.75 - 25, Width / 6, 50));
            map.addBlock(new Block(Width * 0.4, Height / 2, 50, Height / 2));

            map.addEnemy(new BeigeTank(Width * 0.45, Height / 8, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.55, Height / 2, Direction::LEFT, Map::ID++));
            break;

        case 3:
            map = Map(Width / 8, Height * 0.9, Direction::UP);
            map.addBlock(new Block(Width * 0.4, Height * 2/3, 50, Height * 0.75));
            map.addBlock(new Block(Width * 0.8, Height * 0.6, Width / 2, 50));

            map.addEnemy(new BeigeTank(Width / 8, Height / 4, Direction::DOWN, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.6, Height * 0.2, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.8, Height * 0.4, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 2/3, Height * 0.9, Direction::LEFT, Map::ID++));
            break;

        case 4:
            offset = Width / 7;
            map = Map(Width / 2, Height * 0.9, Direction::UP);
            map.addBlock(new Block(offset, Height / 4, offset, 50));
            map.addBlock(new Block(offset * 3.4, Height * 0.6, offset, 50));
            map.addBlock(new Block(offset * 6, Height / 4, offset, 50));

            map.addEnemy(new BeigeTank(offset, Height / 6, Direction::DOWN, Map::ID++));
            map.addEnemy(new BeigeTank(offset * 3.4, Height * 0.5, Direction::DOWN, Map::ID++));
            map.addEnemy(new BeigeTank(offset * 3.4, Height * 0.2, Direction::DOWN, Map::ID++));
            map.addEnemy(new BeigeTank(offset * 6, Height / 6, Direction::DOWN, Map::ID++));
            break;

        case 5:
            map = Map(Width / 6, Height / 2, Direction::RIGHT);
            map.addBlock(new Block(Width / 2, Height / 2, 50, Height / 2));

            map.addEnemy(new GreenTank(Width * 0.75, Height * 0.85, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.75, Height * 0.15, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.5, Height * 0.85, Direction::DOWN, Map::ID++));
            break;

        case 6:
            offset = Width / 3;
            map = Map(offset / 2, Height / 4, Direction::DOWN);
            map.addBlock(new Block(offset - 25, Height / 4, 50, Height / 2));
            map.addBlock(new Block(2 * (offset - 25), Height * 0.8, 50, Height / 2));

            map.addEnemy(new GreenTank(offset * 4/3, Height * 0.25, Direction::DOWN, Map::ID++));
            map.addEnemy(new GreenTank(offset * 7/3, Height * 0.8, Direction::UP, Map::ID++));
            map.addEnemy(new BeigeTank((offset - 25) * 2, Height * 0.25, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank((offset - 25), Height * 0.75, Direction::LEFT, Map::ID++));
            break;

        case 7:
            offset = Width / 2;
            map = Map(offset / 2, Height / 3, Direction::RIGHT);
            map.addBlock(new Block(offset - 25, Height / 2, 50, Height * 0.8));
            map.addBlock(new Block(offset - 25, Height / 2, Width * 0.8, 50));

            map.addEnemy(new GreenTank(offset * 3/2, Height / 3, Direction::DOWN, Map::ID++));
            map.addEnemy(new GreenTank(offset * 3/2, Height * 0.8, Direction::LEFT, Map::ID++));
            map.addEnemy(new GreenTank(offset / 2, Height * 0.8, Direction::UP, Map::ID++));
            break;

        case 8:
            offset = Width / 3;
            map = Map(offset / 2, Height * 0.8, Direction::UP);
            map.addBlock(new Block(offset - 25, Height * 0.8, 50, Height / 2));
            map.addBlock(new Block(2 * (offset - 25), Height / 4, 50, Height / 2));

            map.addEnemy(new GreenTank(offset * 4/3, Height * 0.8, Direction::UP, Map::ID++));
            map.addEnemy(new RedTank(offset * 7/3, Height / 4, Direction::DOWN, Map::ID++));
            map.addEnemy(new BeigeTank((offset - 25) * 2, Height * 0.6, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank((offset - 25), Height * 0.4, Direction::DOWN, Map::ID++));
            break;

        case 9:
            map = Map(Width * 0.2, Height / 2, Direction::RIGHT);
            map.addBlock(new Block(Width / 3, Height / 4, Width / 3, 50));
            map.addBlock(new Block(Width / 3, Height * 0.75, Width / 3, 50));
            map.addBlock(new Block(Width * 0.8, Height / 2, 50, Height / 2));

            map.addEnemy(new GreenTank(Width * 0.9, Height / 2, Direction::UP, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.5, Height * 0.5, Direction::LEFT, Map::ID++));
            map.addEnemy(new RedTank(Width * 0.8, Height / 8, Direction::LEFT, Map::ID++));
            map.addEnemy(new RedTank(Width * 0.8, Height * 7/8, Direction::LEFT, Map::ID++));
            break;

        case 10:
            map = Map(Width / 6, Height * 0.75, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.25, Height * 0.6 , Width / 3, 50));
            map.addBlock(new Block(Width * 0.25 + Width / 6 - 25, Height * 0.6 + Height / 12 + 25, 50, Height / 6));
            map.addBlock(new Block(Width * 0.75, Height / 3, Width / 3, 50));
            map.addBlock(new Block(Width * 0.75 - Width / 6 + 25, Height / 3 - Height / 12 - 25, 50, Height / 6));

            map.addEnemy(new BeigeTank(Width / 4, Height * 0.25, Direction::DOWN, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.8, Height * 0.25, Direction::LEFT, Map::ID++));
            map.addEnemy(new GreenTank(Width * 0.8, Height * 0.75, Direction::LEFT, Map::ID++));
            map.addEnemy(new GreenTank(Width * 0.7, Height * 0.1, Direction::LEFT, Map::ID++));
            break;

        case 11:
            map = Map(Width / 12, Height / 2, Direction::RIGHT);
            map.addBlock(new Block(Width / 8, Height / 2, 50, Height / 3));
            map.addBlock(new Block(Width * 7/8, Height / 2, 50, Height / 3));
            map.addBlock(new Block(Width / 2, Height / 5, Width * 0.4, 50));
            map.addBlock(new Block(Width / 2, Height * 0.8, Width * 0.4, 50));

            map.addEnemy(new BeigeTank(Width / 2, Height / 2, Direction::LEFT, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.9, Height / 6, Direction::LEFT, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.9, Height * 0.9, Direction::LEFT, Map::ID++));
            map.addEnemy(new GreenTank(Width * 11/12, Height / 2, Direction::UP, Map::ID++));
            break;

        case 12:
            map = Map(Width / 12, Height * 2/3, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.45, Height / 3, 50, Height / 3));
            map.addBlock(new Block(Width * 0.55, Height * 0.6, 50, Height / 3));
            map.addBlock(new Block(Width / 4, Height / 5, Width / 12, 50));
            map.addBlock(new Block(Width * 0.75, Height * 0.75, Width / 12, 50));

            map.addEnemy(new RedTank(Width * 0.9, Height / 6, Direction::LEFT, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.8, Height * 0.5, Direction::LEFT, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.6, Height * 2/3, Direction::DOWN, Map::ID++));
            map.addEnemy(new GreenTank(Width * 0.9, Height * 0.25, Direction::UP, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.6, Height * 0.3, Direction::UP, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.35, Height * 0.3, Direction::DOWN, Map::ID++));
            break;
        
        case 13:
            map = Map(Width / 12, Height * 2/3, Direction::RIGHT);
            map.addBlock(new Block(Width / 4, Height / 3, 160, 160));
            map.addBlock(new Block(Width * 0.75, Height / 3, 160, 160));
            map.addBlock(new Block(Width / 4, Height * 2/3, 160, 160));
            map.addBlock(new Block(Width * 0.75, Height * 2/3, 160, 160));

            map.addEnemy(new RedTank(Width * 0.9, 350, Direction::UP, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.8, Height / 2, Direction::LEFT, Map::ID++));
            map.addEnemy(new YellowTank(Width / 2, Height * 0.8, Direction::UP, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.9, Height * 2/3, Direction::DOWN, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.6, Height / 3, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.4, Height * 2/3, Direction::DOWN, Map::ID++));
            break;

        case 14:
            map = Map(Width * 0.8, Height / 10, Direction::LEFT);
            map.addBlock(new Block(Width * 0.8, Height / 5, Width * 0.8, 50));
            map.addBlock(new Block(Width / 3, Height / 2, Width * 0.8, 50));
            map.addBlock(new Block(Width * 0.6, Height * 0.625 + 25, 50, Height / 4));
            map.addBlock(new Block(Width / 4, Height * 0.875, 50, Height / 4));

            map.addEnemy(new RedTank(Width / 10, Height * 0.75, Direction::UP, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.4, Height * 0.8, Direction::RIGHT, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.9, Height * 0.8, Direction::UP, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.6, Height * 0.4, Direction::LEFT, Map::ID++));
            map.addEnemy(new GreenTank(Width * 0.4, Height / 3, Direction::LEFT, Map::ID++));
            break;
        
        case 15:
            map = Map(Width / 10, Height * 0.75, Direction::UP);
            map.addBlock(new Block(Width * 5/6, Height / 2, Width / 3, 50));
            map.addBlock(new Block(Width / 2, Height * 0.125, 50, Height / 4));
            map.addBlock(new Block(Width / 2, Height * 0.875, 50, Height / 4));
            map.addBlock(new Block(Width / 2, Height / 2, 50, Height / 2, true));
            map.addBlock(new Block(Width * 7/12 + 13.5, Height / 2, Width / 6 - 25, 50, true));
            
            map.addEnemy(new RedTank(Width / 10, Height / 10, Direction::RIGHT, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.45, Height * 0.9, Direction::UP, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.9, Height * 0.8, Direction::UP, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.6, Height * 0.4, Direction::LEFT, Map::ID++));
            map.addEnemy(new GreenTank(Width * 0.4, Height / 3, Direction::LEFT, Map::ID++));
            break;
            
        case 16:
            map = Map(Width / 6, Height * 0.85, Direction::RIGHT);
            map.addBlock(new Block(Height * 0.15 + Height * 0.075, Height * 0.7 + 25, Height * 0.15, 50));
            map.addBlock(new Block(Height * 0.075, Height * 0.7 + 25, Height * 0.15, 50, true));
            map.addBlock(new Block(Height * 0.5, Height * 0.775, 50, Height * 0.15));
            map.addBlock(new Block(Height * 0.5, Height * 0.925, 50, Height * 0.15, true));

            map.addBlock(new Block(Width - (Height * 0.15 + Height * 0.075), Height * 0.3 - 25, Height * 0.15, 50));
            map.addBlock(new Block(Width - (Height * 0.075), Height * 0.3 - 25, Height * 0.15, 50, true));
            map.addBlock(new Block(Width - (Height * 0.5), Height * 0.225, 50, Height * 0.15));
            map.addBlock(new Block(Width - (Height * 0.5), Height * 0.075, 50, Height * 0.15, true));

            map.addBlock(new Block(Width / 2, Height / 2, Width / 6, Width / 6));

            map.addEnemy(new PurpleTank(Width / 6, Height * 0.2, Direction::DOWN, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 5/6, Height * 0.8, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank(Width / 2, Height * 0.8, Direction::LEFT, Map::ID++));
            map.addEnemy(new YellowTank(Width * 5/6, Height * 0.2, Direction::LEFT, Map::ID++));
            map.addEnemy(new YellowTank(Width / 2, Height * 0.2, Direction::DOWN, Map::ID++));
            break;

        case 17:
            map = Map(Width * 0.1, Height * 0.1, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.2, Height * 0.25, Width * 0.4, 50));
            map.addBlock(new Block(Width * 0.8, Height * 0.25, Width * 0.4, 50));
            map.addBlock(new Block(Width * 0.2, Height * 0.66, 200, 200));
            map.addBlock(new Block(Width * 0.8, Height * 0.66, 200, 200));

            map.addEnemy(new PurpleTank(Width * 0.8, Height * 0.1, Direction::LEFT, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.4, Height * 0.5, Direction::UP, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.6, Height * 0.5, Direction::UP, Map::ID++));
            map.addEnemy(new WhiteTank(Width / 2, Height * 0.8, Direction::UP, Map::ID++));
            map.addEnemy(new RedTank(Width * 0.1, Height * 0.8, Direction::UP, Map::ID++));
            map.addEnemy(new RedTank(Width * 0.9, Height * 0.8, Direction::UP, Map::ID++));
            break;

        case 18:
            map = Map(Width * 0.5, Height * 0.9, Direction::UP);
            map.addBlock(new Block(Width * 0.4, Height * 0.85, 50, Height * 0.3));
            map.addBlock(new Block(Width * 0.6, Height * 0.85, 50, Height * 0.3));
            map.addBlock(new Block(Width * 0.5, Height * 0.4, Width * 0.4, 50, true));
            map.addBlock(new Block(Width * 0.2, Height * 0.4, Width * 0.2, 50));
            map.addBlock(new Block(Width * 0.8, Height * 0.4, Width * 0.2, 50));

            map.addEnemy(new PurpleTank(Width * 0.8, Height * 0.1, Direction::LEFT, Map::ID++));
            map.addEnemy(new WhiteTank(Width * 0.2, Height * 0.1, Direction::RIGHT, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.8, Height * 0.9, Direction::UP, Map::ID++));
            map.addEnemy(new GreenTank(Width * 0.2, Height * 0.9, Direction::UP, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.5, Height * 0.1, Direction::DOWN, Map::ID++));
            break;

        case 19:
            map = Map(Width * 1/14, Height * 0.1, Direction::DOWN);
            map.addBlock(new Block(Width * 1/7, Height * 0.4, 50, Height * 0.8));
            map.addBlock(new Block(Width * 2/7, Height * 0.6, 50, Height * 0.8, true));
            map.addBlock(new Block(Width * 3/7, Height * 0.4, 50, Height * 0.8));
            map.addBlock(new Block(Width * 4/7, Height * 0.6, 50, Height * 0.8, true));
            map.addBlock(new Block(Width * 5/7, Height * 0.4, 50, Height * 0.8));
            map.addBlock(new Block(Width * 6/7, Height * 0.6, 50, Height * 0.8, true));

            map.addEnemy(new PurpleTank(Width * 2/7, Height * 0.1, Direction::LEFT, Map::ID++));
            map.addEnemy(new WhiteTank(Width * 3/7, Height * 0.9, Direction::LEFT, Map::ID++));
            map.addEnemy(new WhiteTank(Width * 9/14, Height * 0.1, Direction::DOWN, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 6/7, Height * 0.1, Direction::LEFT, Map::ID++));
            break;

        case 20:
            map = Map(Width * 0.1, Height * 0.9, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.05, Height * 0.7, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.15, Height * 0.7, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.25, Height * 0.7, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.35, Height * 0.7, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.4 + 25, Height * 0.45 + 25, 50, Height * 0.5));
            map.addBlock(new Block(Width * 0.85, Height * 0.3, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.95, Height * 0.3, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.75, Height * 0.3, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.65, Height * 0.3, Width * 0.1, 50));

            map.addEnemy(new PinkTank(Width * 0.1, Height * 0.2, Direction::RIGHT, Map::ID++));
            map.addEnemy(new WhiteTank(Width * 0.9, Height * 0.1, Direction::LEFT, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.8, Height * 0.5, Direction::LEFT, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.2, Height * 0.5, Direction::RIGHT, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.5, Height * 0.9, Direction::LEFT, Map::ID++));
            break;
              
        case 21:
            map = Map(Width * 0.125, Height * 0.2, Direction::DOWN);
            map.addBlock(new Block(Width * 0.25, Height * 0.25, 50, Width * 0.5));
            map.addBlock(new Block(Width * 0.25 + Width / 15 + 25, Height * 0.25 + Width * 0.25 - 25, Width * 2/15, 50));
            map.addBlock(new Block(Width * 0.75, Height * 0.75, 50, Width * 0.5));
            map.addBlock(new Block(Width * 0.75 - Width / 15 - 25, Height * 0.75 - Width * 0.25 + 25, Width * 2/15, 50));
            
            map.addEnemy(new PinkTank(Width * 0.5, Height * 0.8, Direction::LEFT, Map::ID++));
            map.addEnemy(new PurpleTank(Width / 3, Height * 0.5, Direction::RIGHT, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.74, Height * 0.2, Direction::LEFT, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.875, Height * 0.8, Direction::UP, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.5, Height * 0.2, Direction::DOWN, Map::ID++));
            break;
            
        case 22:
            map = Map(Width * 0.1, Height * 0.866, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.05, Height * 0.66, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.15, Height * 0.66, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.25, Height * 0.66, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.35, Height * 0.66, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.45, Height * 0.66, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.55, Height * 0.66, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.65, Height * 0.66, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.75, Height * 0.66, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.85, Height * 0.66, Width * 0.1, 50));

            map.addBlock(new Block(Width * 0.15, Height * 0.33, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.25, Height * 0.33, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.35, Height * 0.33, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.45, Height * 0.33, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.55, Height * 0.33, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.65, Height * 0.33, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.75, Height * 0.33, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.85, Height * 0.33, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.95, Height * 0.33, Width * 0.1, 50));

            map.addEnemy(new PurpleTank(Width * 0.9, Height * 0.866, Direction::LEFT, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.5, Height * 0.5, Direction::RIGHT, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.5, Height * 0.166, Direction::LEFT, Map::ID++));
            map.addEnemy(new WhiteTank(Width * 0.05, Height * 0.33, Direction::DOWN, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.95, Height * 0.66, Direction::DOWN, Map::ID++));
            break;
            
        case 23:
            map = Map(Width * 0.2, Height * 0.866, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.2, Height * 0.7, Width * 0.4, 50));
            map.addBlock(new Block(Width * 0.4 + 25, Height * 0.8 - 25, 50, Height * 0.2));
            map.addBlock(new Block(Width * 0.42, Height * 0.2, 50, Height * 0.4));
            map.addBlock(new Block(Width * 0.345 + 25, Height * 0.4 + 25, Width * 0.15, 50));

            map.addBlock(new Block(Width * 0.655 - 25 , Height * 0.6 - 25, Width * 0.15, 50));
            map.addBlock(new Block(Width * 0.58, Height * 0.8, 50, Height * 0.4));
            map.addBlock(new Block(Width * 0.8, Height * 0.3, Width * 0.4, 50));
            map.addBlock(new Block(Width * 0.6 - 25, Height * 0.2 + 25, 50, Height * 0.2));

            map.addEnemy(new WhiteTank(Width * 0.2, Height * 0.144, Direction::DOWN, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.3, Height * 0.1, Direction::DOWN, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.7, Height * 0.9, Direction::UP, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.8, Height * 0.866, Direction::UP, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.8, Height * 0.144, Direction::LEFT, Map::ID++));
            break;
              
        case 24:
            map = Map(Width * 0.2, Height * 0.85, Direction::LEFT);
            map.addBlock(new Block(Width * 0.5, Height * 0.15, 50, Height * 0.3));
            map.addBlock(new Block(Width * 0.5, Height * 0.85, 50, Height * 0.3, true));
            map.addBlock(new Block(Width * 0.5, Height * 0.33, Width * 0.7, 50, true));
            map.addBlock(new Block(Width * 0.5, Height * 0.67, Width * 0.7, 50));

            map.addEnemy(new LimeTank(Width * 0.5, Height * 0.5, Direction::LEFT, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.1, Height * 0.15, Direction::DOWN, Map::ID++));
            map.addEnemy(new WhiteTank(Width * 0.8, Height * 0.15, Direction::DOWN, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.8, Height * 0.85, Direction::UP, Map::ID++));
            break;
            
        case 25:
            map = Map(Width * 0.1, Height * 0.85, Direction::UP);
            map.addBlock(new Block(Width * 0.25, Height * 0.625, 50, Height * 0.75));
            map.addBlock(new Block(Width * 0.5 - 25, Height / 4 - 25, Width * 0.5, 50));
            map.addBlock(new Block(Width * 0.75 - 50, Height * 0.5, 50, Height * 0.5));
            map.addBlock(new Block(Width * 0.625 - 25, Height * 0.75 - 25, Width * 0.25, 50));

            map.addEnemy(new LimeTank(Width * 0.5, Height * 0.5, Direction::LEFT, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.5, Height * 0.1, Direction::LEFT, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.8, Height * 0.5, Direction::UP, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.4, Height * 0.85, Direction::RIGHT, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.1, Height * 0.1, Direction::DOWN, Map::ID++));
            break;
            
        case 26:
            map = Map(Width * 0.05, Height * 0.5, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.125, Height * 0.5, 50, Height * 0.65));
            map.addBlock(new Block(Width * 0.25, Height * 0.5, 50, Height * 0.65));
            map.addBlock(new Block(Width * 0.375, Height * 0.5, 50, Height * 0.65));
            map.addBlock(new Block(Width * 0.5, Height * 0.5, 50, Height * 0.65, true));
            map.addBlock(new Block(Width * 0.625, Height * 0.5, 50, Height * 0.65));
            map.addBlock(new Block(Width * 0.75, Height * 0.5, 50, Height * 0.65));
            map.addBlock(new Block(Width * 0.875, Height * 0.5, 50, Height * 0.65));

            map.addEnemy(new LimeTank(Width * 0.3125, Height * 0.5, Direction::UP, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.4375, Height * 0.5, Direction::DOWN, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.5625, Height * 0.5, Direction::UP, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.6875, Height * 0.5, Direction::DOWN, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.8125, Height * 0.5, Direction::UP, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.9375, Height * 0.5, Direction::DOWN, Map::ID++));
            break;
              
        case 27:
            map = Map(Width * 0.1, Height * 0.866, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.05, Height * 0.7, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.15, Height * 0.7, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.45, Height * 0.7, Width * 0.5, 50));
            map.addBlock(new Block(Width * 0.7 - 25, Height * 0.6 - 25, 50, Height * 0.2));
            map.addBlock(new Block(Width * 0.95, Height * 0.3, Width * 0.1, 50));
            map.addBlock(new Block(Width * 0.85, Height * 0.3, Width * 0.1, 50, true));
            map.addBlock(new Block(Width * 0.55, Height * 0.3, Width * 0.5, 50));
            map.addBlock(new Block(Width * 0.3 + 25, Height * 0.4 + 25, 50, Height * 0.2));

            map.addEnemy(new LimeTank(Width * 0.9, Height * 0.1, Direction::LEFT, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.1, Height * 0.1, Direction::DOWN, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.5, Height * 0.5, Direction::RIGHT, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.9, Height * 0.5, Direction::DOWN, Map::ID++));
            map.addEnemy(new WhiteTank(Width * 0.1, Height * 0.6, Direction::RIGHT, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.9, Height * 0.866, Direction::LEFT, Map::ID++));
            break;
            
        case 28:
            map = Map(Width * 0.15, Height * 0.5, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.5, Height * 0.5, Height * 0.6, Height * 0.6));

            map.addEnemy(new BlackTank(Width * 0.8, Height * 0.1, Direction::LEFT, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.9, Height * 0.5, Direction::LEFT, Map::ID++));
            map.addEnemy(new PurpleTank(Width * 0.8, Height * 0.9, Direction::LEFT, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.5, Height * 0.9, Direction::LEFT, Map::ID++));
            map.addEnemy(new WhiteTank(Width * 0.5, Height * 0.1, Direction::LEFT, Map::ID++));
            break;
            
        case 29:
            map = Map(Width * 0.1, Height * 0.7, Direction::UP);
            map.addBlock(new Block(Width * 0.25, Height * 2/3, 50, Height * 2/3));
            map.addBlock(new Block(Width * 0.5, Height / 3, 50, Height * 2/3, true));
            map.addBlock(new Block(Width * 0.75, Height * 0.6, Width * 0.25, Width * 0.25));

            map.addEnemy(new PurpleTank(Width * 0.3, Height * 0.1, Direction::LEFT, Map::ID++));
            map.addEnemy(new BlackTank(Width * 0.75, Height * 0.1, Direction::LEFT, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.75, Height * 0.3, Direction::DOWN, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.5, Height * 0.85, Direction::LEFT, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.3, Height * 0.85, Direction::UP, Map::ID++));
            break;
             
        case 30:
            map = Map(Width * 0.1, Height * 0.5, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.25, Height * 0.25, 50, Height * 0.25));
            map.addBlock(new Block(Width * 0.25, Height * 0.75, 50, Height * 0.25));
            map.addBlock(new Block(Width * 0.75, Height * 0.5, 50, Height * 0.75));

            map.addEnemy(new PurpleTank(Width * 0.375, Height * 0.25, Direction::LEFT, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.625, Height * 0.75, Direction::LEFT, Map::ID++));
            map.addEnemy(new PinkTank(Width * 0.5, Height * 0.125, Direction::LEFT, Map::ID++));
            map.addEnemy(new LimeTank(Width * 0.5, Height * 0.875, Direction::LEFT, Map::ID++));
            map.addEnemy(new BlackTank(Width * 0.875, Height * 0.25, Direction::DOWN, Map::ID++));
            map.addEnemy(new BlackTank(Width * 0.875, Height * 0.75, Direction::UP, Map::ID++));
            break;
            
        default:
            break;
    }

    return map;
}