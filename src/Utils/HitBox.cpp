#include "HitBox.hpp"

bool CustomHitbox::equals(CustomHitbox h) {
    return this->left() == h.left() && this->top() == h.top() &&
           this->right() == h.right() && this->bottom() == h.bottom();
}

bool CustomHitbox::collision(CustomHitbox b1, CustomHitbox b2) {
    return (b1.left() <= b2.right() && b1.right() >= b2.left()) && 
        (b1.bottom() >= b2.top() && b1.top() <= b2.bottom());
}

std::pair<double, double> CustomHitbox::collisionMargins(CustomHitbox b1, CustomHitbox b2) {
    double xa = b2.left() - b1.right();
    double xb = b2.right() - b1.left();
    double xMin = abs(xa) < abs(xb) ? xa : xb;

    double ya = b2.top() - b1.bottom();
    double yb = b2.bottom() - b1.top();
    double yMin = abs(ya) < abs(yb) ? ya : yb;

    return std::pair(xMin, yMin);
}

void CustomHitbox::draw() {
    DrawRectangleLines(this->left(), this->top(), this->box.width, 
                       this->box.height, (Color){255, 0, 0, 255});
}