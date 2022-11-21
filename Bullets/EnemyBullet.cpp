#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(int x, int y) :
        DefaultBullet(x, y, 1) {
}

EnemyBullet::~EnemyBullet() {}

void EnemyBullet::Move() {
    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;
    GameObject::Translate(0, 9);

    if (yPos > 1000) {
        this->alive = false;
    }
}


