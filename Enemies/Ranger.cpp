#include "Ranger.h"


Ranger::Ranger(int x, int y) :
        GameObject("../Assets/Ranger.png", x, y,  256,3,0){
    this->xPos = x;
    this->yPos = y;
    this->fric = 0.95;
    this->tX = 0.0;
    this->tY = 0.0;
    this->life = 3;
}

Ranger::~Ranger() {

}

void Ranger::Move() {
    xPos += (int)tX;
    yPos += (int)tY;
    tX *= fric;
    tY *= fric;
    if (yPos>800){
        alive = false;
    }
    GameObject::Translate(0, 2);
}

void Ranger::TakeHit() {
    this->life--;
    if(life==0){
        GameObject::Destroy();
    }
}

