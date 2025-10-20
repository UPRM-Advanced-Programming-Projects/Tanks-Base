#include "Map.hpp"

void Map::draw() {
    for (Tank* e : this->enemies) {
        BeigeTank* b = dynamic_cast<BeigeTank*>(e);
        GreenTank* g = dynamic_cast<GreenTank*>(e);
        RedTank* r = dynamic_cast<RedTank*>(e);
        YellowTank* y = dynamic_cast<YellowTank*>(e);

        if (b) {
            b->draw();
            if (showHitboxes) b->drawHitboxes();
        } else if (g) {
            g->draw();
            if (showHitboxes) g->drawHitboxes();
        } else if (r) {
            r->draw();
            if (showHitboxes) r->drawHitboxes();
        } else if (y) {
            y->draw();
            if (showHitboxes) y->drawHitboxes();
        }
    }

    for (Block* b : this->layout) b->draw();
}
        
void Map::update(Player* &player, std::vector<Projectile*> &projectiles) {

    this->enemies.erase(remove_if(this->enemies.begin(), this->enemies.end(), [](Tank* e) {
        return e->getHealth() <= 0;
    }), this->enemies.end());
    
    for (Tank* e : this->enemies) {
        BeigeTank* b = dynamic_cast<BeigeTank*>(e);
        GreenTank* g = dynamic_cast<GreenTank*>(e);
        RedTank* r = dynamic_cast<RedTank*>(e);
        YellowTank* y = dynamic_cast<YellowTank*>(e);

        if (b) {
            b->update();
            b->targetSystem(player->getHitbox(), this->layout);
            b->shoot(projectiles, player->getPosition());
            b->projectileCollision(projectiles);
        } else if (g) {
            g->update();
            g->targetSystem(player->getHitbox(), this->layout);
            g->move(this->layout);
            g->shoot(projectiles, player->getPosition());
            g->projectileCollision(projectiles);
        } else if (r) {
            r->update();
            r->move(this->layout);
            r->shoot(projectiles);
            r->projectileCollision(projectiles);
        } else if (y) {
            y->update();
            y->targetSystem(player->getHitbox(), this->layout);
            y->move(this->layout);
            y->shoot(projectiles, player->getPosition());
            y->projectileCollision(projectiles);
        }
    }
    
    for (Projectile* &p : projectiles) {
        p->update(this->layout, player->getHitbox());
    }
    
    player->update();
    player->controls(this->layout, this->getEnemyHitboxes());
    player->projectileCollision(projectiles);
    Projectile::cleanProjectiles(projectiles);
    Projectile::projectileCollision(projectiles);

}

Map Map::getMap(int level) {
    Map map;
    double offset;

    switch (level){
        case 1:
            map = Map(Width / 2, Height / 3, Direction::DOWN);
            map.addBlock(new Block(Width / 2, Height / 2, Width / 2, 50));

            map.addEnemy(new BeigeTank(Width / 2, Height * 2/3, Direction::UP, Map::ID++));
            break;

        case 2:
            map = Map(Width / 8, Height * 0.9, Direction::UP);
            map.addBlock(new Block(Width * 0.4, Height * 2/3, 50, Height * 0.75));
            map.addBlock(new Block(Width * 0.8, Height * 0.6, Width / 2, 50));

            map.addEnemy(new BeigeTank(Width / 8, Height / 4, Direction::DOWN, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.6, Height * 0.2, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.8, Height * 0.4, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 2/3, Height * 0.9, Direction::LEFT, Map::ID++));
            break;

        case 3:
            offset = Width / 3;
            map = Map(offset / 2, Height / 4, Direction::DOWN);
            map.addBlock(new Block(offset - 25, Height / 4, 50, Height / 2));
            map.addBlock(new Block(2 * (offset - 25), Height * 0.8, 50, Height / 2));

            map.addEnemy(new GreenTank(offset * 4/3, Height * 0.25, Direction::DOWN, Map::ID++));
            map.addEnemy(new GreenTank(offset * 7/3, Height * 0.8, Direction::UP, Map::ID++));
            map.addEnemy(new BeigeTank((offset - 25) * 2, Height * 0.25, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank((offset - 25), Height * 0.75, Direction::LEFT, Map::ID++));
            break;

        case 4:
            offset = Width / 3;
            map = Map(offset / 2, Height * 0.8, Direction::UP);
            map.addBlock(new Block(offset - 25, Height * 0.8, 50, Height / 2));
            map.addBlock(new Block(2 * (offset - 25), Height / 4, 50, Height / 2));

            map.addEnemy(new GreenTank(offset * 4/3, Height * 0.8, Direction::UP, Map::ID++));
            map.addEnemy(new RedTank(offset * 7/3, Height / 4, Direction::DOWN, Map::ID++));
            map.addEnemy(new BeigeTank((offset - 25) * 2, Height * 0.6, Direction::LEFT, Map::ID++));
            map.addEnemy(new BeigeTank((offset - 25), Height * 0.4, Direction::DOWN, Map::ID++));
            break;

        case 5:
            map = Map(Width * 0.2, Height / 2, Direction::RIGHT);
            map.addBlock(new Block(Width / 3, Height / 4, Width / 3, 50));
            map.addBlock(new Block(Width / 3, Height * 0.75, Width / 3, 50));
            map.addBlock(new Block(Width * 0.8, Height / 2, 50, Height / 2));

            map.addEnemy(new GreenTank(Width * 0.9, Height / 2, Direction::UP, Map::ID++));
            map.addEnemy(new BeigeTank(Width * 0.5, Height * 0.5, Direction::LEFT, Map::ID++));
            map.addEnemy(new RedTank(Width * 0.8, Height / 8, Direction::LEFT, Map::ID++));
            map.addEnemy(new RedTank(Width * 0.8, Height * 7/8, Direction::LEFT, Map::ID++));
            break;

        case 6:
            map = Map(Width / 12, Height / 2, Direction::RIGHT);
            map.addBlock(new Block(Width / 8, Height / 2, 50, Height / 3));
            map.addBlock(new Block(Width * 7/8, Height / 2, 50, Height / 3));
            map.addBlock(new Block(Width / 2, Height / 5, Width * 0.4, 50));
            map.addBlock(new Block(Width / 2, Height * 0.8, Width * 0.4, 50));

            map.addEnemy(new BeigeTank(Width / 2, Height / 2, Direction::LEFT, Map::ID++));
            map.addEnemy(new GreenTank(Width / 2, Height / 3, Direction::DOWN, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.9, Height / 6, Direction::LEFT, Map::ID++));
            map.addEnemy(new YellowTank(Width * 0.9, Height * 0.9, Direction::LEFT, Map::ID++));
            map.addEnemy(new GreenTank(Width * 11/12, Height / 2, Direction::UP, Map::ID++));
            break;

        case 7:
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
            
        default:
            break;
    }

    return map;
}