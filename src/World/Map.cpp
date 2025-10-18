#include "Map.hpp"

void Map::draw() {
    for (BeigeTank* e : this->enemies1) {
        e->draw();
        if (showHitboxes) e->drawHitboxes();
    }
    for (GreenTank* e : this->enemies2) {
        e->draw();
        if (showHitboxes) e->drawHitboxes();
    }
    for (RedTank* e : this->enemies3) {
        e->draw();
        if (showHitboxes) e->drawHitboxes();
    }
    for (YellowTank* e : this->enemies4) {
        e->draw();
        if (showHitboxes) e->drawHitboxes();
    }

    for (Block* b : this->layout) b->draw();
}
        
void Map::update(Player* &player, std::vector<Projectile*> &projectiles) {

    this->enemies1.erase(remove_if(this->enemies1.begin(), this->enemies1.end(), [](BeigeTank* e) {
        return e->getHealth() <= 0;
    }), this->enemies1.end());

    this->enemies2.erase(remove_if(this->enemies2.begin(), this->enemies2.end(), [](GreenTank* e) {
        return e->getHealth() <= 0;
    }), this->enemies2.end());
    
    this->enemies3.erase(remove_if(this->enemies3.begin(), this->enemies3.end(), [](RedTank* e) {
        return e->getHealth() <= 0;
    }), this->enemies3.end());

    this->enemies4.erase(remove_if(this->enemies4.begin(), this->enemies4.end(), [](YellowTank* e) {
        return e->getHealth() <= 0;
    }), this->enemies4.end());
    
    for (BeigeTank* e : this->enemies1) {
        e->update();
        e->targetSystem(player->getHitbox(), this->layout);
        e->shoot(projectiles, player->getPosition());
        e->projectileCollision(projectiles);
    }
    for (GreenTank* e : this->enemies2) {
        e->update();
        e->targetSystem(player->getHitbox(), this->layout);
        e->move(this->layout);
        e->shoot(projectiles, player->getPosition());
        e->projectileCollision(projectiles);
    }
    for (RedTank* e : this->enemies3) {
        e->update();
        e->move(this->layout);
        e->shoot(projectiles);
        e->projectileCollision(projectiles);
    }
    for (YellowTank* e : this->enemies4) {
        e->update();
        e->targetSystem(player->getHitbox(), this->layout);
        e->move(this->layout);
        e->shoot(projectiles, player->getPosition());
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

}

Map Map::getMap(int level) {
    Map map;
    double offset;

    switch (level){
        case 1:
            map = Map(Width / 2, Height / 3, Direction::DOWN);
            map.addBlock(new Block(Width / 2, Height / 2, Width / 2, 50));

            map.addBeige(new BeigeTank(Width / 2, Height * 2/3, Direction::UP, Map::ID++));
            break;

        case 2:
            map = Map(Width / 8, Height * 0.9, Direction::UP);
            map.addBlock(new Block(Width * 0.4, Height * 2/3, 50, Height * 0.75));
            map.addBlock(new Block(Width * 0.8, Height * 0.6, Width / 2, 50));

            map.addBeige(new BeigeTank(Width / 8, Height / 4, Direction::DOWN, Map::ID++));
            map.addBeige(new BeigeTank(Width * 0.6, Height * 0.2, Direction::LEFT, Map::ID++));
            map.addBeige(new BeigeTank(Width * 0.8, Height * 0.4, Direction::LEFT, Map::ID++));
            map.addBeige(new BeigeTank(Width * 2/3, Height * 0.9, Direction::LEFT, Map::ID++));
            break;

        case 3:
            offset = Width / 3;
            map = Map(offset / 2, Height / 4, Direction::DOWN);
            map.addBlock(new Block(offset - 25, Height / 4, 50, Height / 2));
            map.addBlock(new Block(2 * (offset - 25), Height * 0.8, 50, Height / 2));

            map.addGreen(new GreenTank(offset * 4/3, Height * 0.25, Direction::DOWN, Map::ID++));
            map.addGreen(new GreenTank(offset * 7/3, Height * 0.8, Direction::UP, Map::ID++));
            map.addBeige(new BeigeTank((offset - 25) * 2, Height * 0.25, Direction::LEFT, Map::ID++));
            map.addBeige(new BeigeTank((offset - 25), Height * 0.75, Direction::LEFT, Map::ID++));
            break;

        case 4:
            offset = Width / 3;
            map = Map(offset / 2, Height * 0.8, Direction::UP);
            map.addBlock(new Block(offset - 25, Height * 0.8, 50, Height / 2));
            map.addBlock(new Block(2 * (offset - 25), Height / 4, 50, Height / 2));

            map.addGreen(new GreenTank(offset * 4/3, Height * 0.8, Direction::UP, Map::ID++));
            map.addRed(new RedTank(offset * 7/3, Height / 4, Direction::DOWN, Map::ID++));
            map.addBeige(new BeigeTank((offset - 25) * 2, Height * 0.6, Direction::LEFT, Map::ID++));
            map.addBeige(new BeigeTank((offset - 25), Height * 0.4, Direction::DOWN, Map::ID++));
            break;

        case 5:
            map = Map(Width * 0.2, Height / 2, Direction::RIGHT);
            map.addBlock(new Block(Width / 3, Height / 4, Width / 3, 50));
            map.addBlock(new Block(Width / 3, Height * 0.75, Width / 3, 50));
            map.addBlock(new Block(Width * 0.8, Height / 2, 50, Height / 2));

            map.addGreen(new GreenTank(Width * 0.9, Height / 2, Direction::UP, Map::ID++));
            map.addBeige(new BeigeTank(Width * 0.5, Height * 0.5, Direction::LEFT, Map::ID++));
            map.addRed(new RedTank(Width * 0.8, Height / 8, Direction::LEFT, Map::ID++));
            map.addRed(new RedTank(Width * 0.8, Height * 7/8, Direction::LEFT, Map::ID++));
            break;

        case 6:
            map = Map(Width / 12, Height / 2, Direction::RIGHT);
            map.addBlock(new Block(Width / 8, Height / 2, 50, Height / 3));
            map.addBlock(new Block(Width * 7/8, Height / 2, 50, Height / 3));
            map.addBlock(new Block(Width / 2, Height / 5, Width * 0.4, 50));
            map.addBlock(new Block(Width / 2, Height * 0.8, Width * 0.4, 50));

            map.addBeige(new BeigeTank(Width / 2, Height / 2, Direction::LEFT, Map::ID++));
            map.addYellow(new YellowTank(Width * 0.9, Height / 6, Direction::LEFT, Map::ID++));
            map.addYellow(new YellowTank(Width * 0.9, Height * 0.9, Direction::LEFT, Map::ID++));
            map.addGreen(new GreenTank(Width * 11/12, Height / 2, Direction::UP, Map::ID++));
            break;

        case 7:
            map = Map(Width / 12, Height * 2/3, Direction::RIGHT);
            map.addBlock(new Block(Width * 0.45, Height / 3, 50, Height / 3));
            map.addBlock(new Block(Width * 0.55, Height * 0.6, 50, Height / 3));
            map.addBlock(new Block(Width / 4, Height / 5, Width / 12, 50));
            map.addBlock(new Block(Width * 0.75, Height * 0.75, Width / 12, 50));

            map.addRed(new RedTank(Width * 0.9, Height / 6, Direction::LEFT, Map::ID++));
            map.addYellow(new YellowTank(Width * 0.8, Height * 0.5, Direction::LEFT, Map::ID++));
            map.addYellow(new YellowTank(Width * 0.6, Height * 2/3, Direction::DOWN, Map::ID++));
            map.addGreen(new GreenTank(Width * 0.9, Height * 0.25, Direction::UP, Map::ID++));
            map.addBeige(new BeigeTank(Width * 0.6, Height * 0.3, Direction::UP, Map::ID++));
            map.addBeige(new BeigeTank(Width * 0.35, Height * 0.3, Direction::DOWN, Map::ID++));
            break;
            
        default:
            break;
    }

    return map;
}