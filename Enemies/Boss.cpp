//
// Created by Saad Zubairi on 11/14/2022.
//

#include "Boss.h"

Boss::Boss(int x, int y) : GameObject("../Assets/BOSS.png", x, y,  128,1,2) {

}

Boss::~Boss() {

}

void Boss::Render() {
    GameObject::Render();
}

void Boss::Move() {
    xPos += (int)tX;
    yPos += (int)tY;
    tX *= fric;
    tY *= fric;
    GameObject::Translate(0, -1);

    if (yPos<0){
        this->alive = false;
        /*yPos = Game::height;*/
    }
}
