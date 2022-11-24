#include "PlayerShip.h"
#include "Game.h"

PlayerShip::PlayerShip(int x, int y) :
        GameObject("../Assets/SHIPS.png", x, y, 768, 256, 1, 3, 0.5) {
    this->xPos = x;
    this->yPos = y;
    this->fric = 0.85;
    this->tX = 0.0;
    this->tY = 0.0;
    hit = false;
}

PlayerShip::~PlayerShip() {

}

void PlayerShip::Move() {
    if (hit == false) {
        xPos += (int) tX;
        yPos += (int) tY;
        tX *= fric;
        tY *= fric;
        if (xPos > Game::width) {
            xPos = 0;
        }
        if (xPos < -128) {
            xPos = Game::width;
        }
    }
    if (xVel != 0 || yVel != 0) {
        GameObject::Translate(xVel, yVel);
    }
}

void PlayerShip::TakeHit() {
    hit = true;
}

