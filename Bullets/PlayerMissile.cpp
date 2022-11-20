#include "PlayerMissile.h"

PlayerMissile::PlayerMissile(int x, int y, GameObject *enemy) :
        DefaultBullet(x, y, 2) {
    this->enemy = enemy;
    life = 0;
}

PlayerMissile::~PlayerMissile() {}

void PlayerMissile::Move() {
    xFactor = 0;
    dX = enemy->xPos - xPos;
    dY = enemy->yPos - yPos;
    slope = dY / dX;
    xFactor = dY / slope;
    xFactor = xFactor / 30;

    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;
    life++;
    GameObject::Translate(xFactor, dY / 20);
    if (yPos > 1000) {
        this->alive = false;
    }
    if (life > 180) {
        this->alive = false;
    }
}

void PlayerMissile::Render() {
    angle = ((dX) == 0) ? -90 : atan((dY) / (dX)) * 180.0 / M_PI;
    if (dX < 0) {
        angle += 180;
    }
    SDL_RenderCopyEx(Game::renderer, objTexture, &gSpriteClips[Counters::spriteFrame % 3],
                     &destR, angle + 90, NULL, SDL_FLIP_NONE);
}

/*void NimbleBullet::Move() {


}*/
