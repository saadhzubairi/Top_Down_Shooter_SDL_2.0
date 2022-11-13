#include "PlayerShip.h"
#include "Game.h"

PlayerShip::PlayerShip(int x, int y) :
GameObject("../Assets/SHIPS.png", x, y, 256,3,0) {
    this->xPos = x;
    this->yPos = y;
    this->fric = 0.95;
    this->tX = 0.0;
    this->tY = 0.0;
    hit = false;
}

PlayerShip::~PlayerShip() {

}

void PlayerShip::Move() {
    if(hit == false){
        xPos += (int) tX;
        yPos += (int) tY;
        tX *= fric;
        tY *= fric;
        if(xPos>Game::width){
            xPos = 0;
        }
        if(xPos< -128){
            xPos = Game::width;
        }
    }
}

void PlayerShip::TakeHit() {
    hit = true;
}

