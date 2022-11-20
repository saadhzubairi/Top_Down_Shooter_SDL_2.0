#include "NimbleBullet.h"
#include <stdio.h>
#include "../Game.h"

NimbleBullet::NimbleBullet(int x, int y) :
        DefaultBullet(x, y, 1) {

    xFactor = 0;
    dX = Game::player->xPos - xPos;
    dY = Game::player->yPos - yPos;
    slope = dY / dX;
    xFactor = dY / slope;
    yFactor = slope;
    xFactor = xFactor / 30;
    yFactor = dY/30;

    this->angle = ((dX) == 0) ?-90:atan((dY) / (dX)) * 180.0 / M_PI;
    if (dX > 0) {
        angle += 180;
    }
}

NimbleBullet::~NimbleBullet() {

}

void NimbleBullet::Move() {

    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;

    GameObject::Translate(xFactor, yFactor);
    if (yPos > 1000) {
        this->alive = false;
    }
}

void NimbleBullet::Render() {
    SDL_RenderCopyEx(Game::renderer, objTexture, &gSpriteClips[Counters::spriteFrame % 3],
                     &destR, angle + 90, NULL, SDL_FLIP_NONE);
}