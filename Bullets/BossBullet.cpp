#include "BossBullet.h"


BossBullet::BossBullet(int x, int y) : DefaultBullet(x, y, 3) {

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

BossBullet::~BossBullet() {

}

void BossBullet::Move() {
    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;

    GameObject::Translate(xFactor, yFactor);
    if (yPos > 1000) {
        this->alive = false;
    }
}

void BossBullet::Render() {
    SDL_RenderCopyEx(Game::renderer, objTexture, &spriteSourceRects[Counters::spriteFrame % this->NumOfSprites],
                     &destR, angle + 90, NULL, SDL_FLIP_NONE);
}


