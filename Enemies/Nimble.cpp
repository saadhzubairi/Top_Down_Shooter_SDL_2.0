#include "Nimble.h"

Nimble::Nimble(int x, int y) :
        GameObject("../Assets/Nimble.png", x, y,  768,256,1,3,0.5) {
    this->xPos = x;
    this->yPos = y;
    this->fric = 0.95;
    this->tX = 0.0;
    this->tY = 0.0;
    this->life = 1;

}

Nimble::~Nimble() {

}

void Nimble::Move() {
    xPos += (int)tX;
    yPos += (int)tY;
    tX *= fric;
    tY *= fric;
    if (yPos>800){
        alive = false;
    }
    GameObject::Translate(0, 3);
}

void Nimble::TakeHit() {
    this->life--;
    if(life==0){
        GameObject::Destroy();
    }
}
