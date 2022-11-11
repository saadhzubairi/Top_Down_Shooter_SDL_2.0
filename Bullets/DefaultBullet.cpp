#include "DefaultBullet.h"
#include "../Game.h"

DefaultBullet::DefaultBullet(int x, int y, int type) : GameObject(
        "../Assets/Bullets_ship.png", x, y,  256,3) {


    /*
     * 0: Ship Bullet
     * 1: Enemy Bullet
     * 2: Ship Missile*/

    switch (type) {
        case 0:
            setObjTexture("../Assets/Bullets_ship.png", 256, 3);
            break;
        case 1:
            setObjTexture("../Assets/Bullets_enemy.png", 256, 3);
            break;
        case 2:
            setObjTexture("../Assets/Missiles_ship.png", 256, 3);
            break;
        default:
            break;
    }


    this->xPos = x;
    this->yPos = y;
    this->fric = 0.95;
    this->tX = 0.0;
    this->tY = 0.0;
}


DefaultBullet::~DefaultBullet() {

}

void DefaultBullet::Move() {
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

void DefaultBullet::Render() {
    GameObject::Render();
}
