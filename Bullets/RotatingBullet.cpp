#include "RotatingBullet.h"

RotatingBullet::RotatingBullet(int x, int y) : DefaultBullet(x, y, 1) {}

RotatingBullet::~RotatingBullet() = default;

void RotatingBullet::Move() {
    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;
    GameObject::Translate(0, 0);
}

void RotatingBullet::Render() {


    float dX = Game::player->xPos - xPos;
    float dY = Game::player->yPos - yPos;


    double angle = ((dX) == 0) ?
                   -90
                               :
                   atan((dY) / (dX)) * 180.0 / M_PI;

    if (dX > 0) {angle += 180;}
    SDL_RenderCopyEx(Game::renderer, objTexture,
                     &spriteSourceRects[0], &destR,
                     angle + 90, NULL, SDL_FLIP_NONE);
}




