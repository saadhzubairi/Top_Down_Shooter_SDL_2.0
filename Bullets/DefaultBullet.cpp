#include "DefaultBullet.h"
#include "../Game.h"

DefaultBullet::DefaultBullet(int x, int y, int type) : GameObject(
        "../Assets/Bullets_ship.png", x, y, 768, 256, 1, 3, 0.5) {
    switch (type) {
        case 0:
            setObjTexture("../Assets/Bullets_ship.png", 768,256,1,3,0.5);
            break;
        case 1:
            setObjTexture("../Assets/Bullets_enemy.png",768,256,1,3,0.5);
            break;
        case 2:
            setObjTexture("../Assets/Missiles_ship.png",768,256,1,3,0.5);
            break;
        case 3:
            setObjTexture("../Assets/BossBullet.png",  1024,256,1,4,0.25);
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


DefaultBullet::~DefaultBullet() {}

void DefaultBullet::Move() {
    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;
    GameObject::Translate(0, -30);
    if (yPos < 0) {this->alive = false;}
}

void DefaultBullet::Render() {
    GameObject::Render();
}

void DefaultBullet::Update() {
    GameObject::Update();
    this->xMin = xPos - ObjWidth / 2 + 70;
    this->xMax = xMin + ObjWidth - 135;
}