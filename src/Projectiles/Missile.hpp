#include "Projectile.hpp"

class Missile : public Projectile {
    protected:
        std::pair<double, double> target;
        std::pair<double, double> velocity;
        double angle;
        float speed;

    public:
        Missile(double x, double y, int ricochet, float speed, int ID) : Projectile(x, y, ricochet) {
            this->position.first = x;
            this->position.second = y;
            this->speed = speed;
            this->angle = (180 / PI) * atan2((GetMousePosition().y - y), (GetMousePosition().x - x));
            this->velocity.first = cos(angle * PI / 180);
            this->velocity.second = sin(angle * PI / 180);
            this->hitbox.setSize(8, 8);
            this->ID = ID;
        }

        Missile(double x, double y, int ricochet, float speed, std::pair<double, double> target, int ID) : Projectile(x, y, ricochet) {
            this->position.first = x;
            this->position.second = y;
            this->speed = speed;
            this->angle = (180 / PI) * atan2((target.second - y), (target.first - x));
            this->velocity.first = cos(angle * PI / 180);
            this->velocity.second = sin(angle * PI / 180);
            this->hitbox.setSize(5, 5);
            this->ID = ID;
        }

        void bounceX();
        void bounceY();
        Vector2 reflect(Vector2 v, Vector2 n);

        void update(std::vector<Block*> blocks, CustomHitbox target) override;
        void draw() override;
};