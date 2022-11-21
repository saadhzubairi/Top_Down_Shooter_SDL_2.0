#include "Turret.h"

Turret::Turret(int x, int y) : GameObject("../Assets/turret.png", x, y, 128, 128, 1, 1, 1.5) {
    life = 3;
}

void Turret::Move() {
    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;

    if (yPos > 247) {
        GameObject::Translate(0, sin(Counters::spriteFrame / 50) * 2);

    } else {
        GameObject::Translate(0, 2);
    }
}

void Turret::Render() {

    float dX = Game::player->xPos - xPos;
    float dY = Game::player->yPos - yPos;

    double angle = atan2((dY), (dX)) * 180.0 / M_PI;
    angle += 180;

    SDL_RenderCopyEx(Game::renderer, objTexture, &spriteSourceRects[Counters::spriteFrame % this->NumOfSprites],
                     &destR, angle + 90, NULL, SDL_FLIP_NONE);
}

Turret::~Turret() {

}

void Turret::TakeHit() {
    life--;
    if(life<0){
        alive = false;
        Game::booms.push_back(new Boom(xPos,yPos));
    }

}
