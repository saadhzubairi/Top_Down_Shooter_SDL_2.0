#include "PlayerBullet.h"
#include "../Game.h"
PlayerBullet::PlayerBullet(const char *textureSheet, int x, int y, int sheetSizeXy, int numSprites) : GameObject(
        textureSheet, x, y, sheetSizeXy, numSprites) {
    this->xPos = x;
    this->yPos = y;
    this->fric = 0.95;
    this->tX = 0.0;
    this->tY = 0.0;
}


PlayerBullet::~PlayerBullet() {

}

void PlayerBullet::Move() {
    xPos += (int)tX;
    yPos += (int)tY;
    tX *= fric;
    tY *= fric;
    GameObject::Translate(0, -19);

    if (yPos<0){
        this->alive = false;
        /*yPos = Game::height;*/
    }
}