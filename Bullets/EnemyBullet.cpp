#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(const char *textureSheet, int x, int y, int sheetSizeXy, int numSprites) : PlayerBullet(
        textureSheet, x, y, sheetSizeXy, numSprites) {
}

EnemyBullet::~EnemyBullet() {

}

void EnemyBullet::Move() {
    xPos += (int)tX;
    yPos += (int)tY;
    tX *= fric;
    tY *= fric;
    GameObject::Translate(0, 9);

    if (yPos>1000){
        this->alive = false;
    }
}


