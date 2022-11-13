#include "NimbleBullet.h"
#include <stdio.h>
#include "../Game.h"

NimbleBullet::NimbleBullet(int TarX, int TarY, int x, int y) :
        DefaultBullet(x, y, 1) {
    this->TarX = TarX;
    this->TarY = TarY;

    xFactor = 0;
    dX = TarX - xPos;
    dY = TarY - yPos;
    slope = dY / dX;
    xFactor = dY / slope;
    xFactor = xFactor / 45;

    //printf("xFactor = %d ; dX,dY: [%d,%d]; slope: %f :: %f\n",xFactor*50,dX,dY,slope,xff);
}

NimbleBullet::~NimbleBullet() {

}

void NimbleBullet::Move() {

    xFactor = 0;
    dX = Game::player->xPos - xPos;
    dY = Game::player->yPos - yPos;
    slope = dY / dX;
    xFactor = dY / slope;
    xFactor = xFactor / 30;

    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;

    GameObject::Translate(xFactor, 9);
    if (yPos > 1000) {
        this->alive = false;
    }
}

void NimbleBullet::Render() {

    float dX = Game::player->xPos - xPos;
    float dY = Game::player->yPos - yPos;


    double angle = ((dX) == 0) ?
                   -90
                               :
                   atan((dY) / (dX)) * 180.0 / M_PI;

    if (dX > 0) {
        angle += 180;
    }

    if(angle<0 && angle> (-90)){
        if(angle> (-30))  angle = -30;
    }
    else if(angle>180 && angle < 270){
        if (angle < 210) angle = 210;
    }
    else if(angle>0 && angle < 90){
        angle = -30;
    }
    else if(angle>90 && angle < 180){
        angle = 210;
    }


    SDL_RenderCopyEx(Game::renderer, objTexture, &gSpriteClips[curSprite], &destR, angle + 90, NULL, SDL_FLIP_NONE);
    frame++;
    if (frame % 60 == 0) {
        curSprite++;
        if (curSprite > 2) {
            curSprite = 0;
        }
    }
}