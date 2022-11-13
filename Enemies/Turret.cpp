#include "Turret.h"

Turret::Turret(int x, int y) : GameObject("../Assets/turret.png", x, y,  128,1,1) {

}

void Turret::Move() {
    xPos += (int) tX;
    yPos += (int) tY;
    tX *= fric;
    tY *= fric;
    GameObject::Translate(0, 0);
}

void Turret::Render() {
    float dX = Game::player->xPos - xPos;
    float dY = Game::player->yPos - yPos;


    double angle = ((dX) == 0) ?
                   -90
                               :
                   atan((dY) / (dX)) * 180.0 / M_PI;

    if (dX > 0) {
        angle += 180;
    }
    SDL_RenderCopyEx(Game::renderer, objTexture, &gSpriteClips[0], &destR, angle + 90, NULL, SDL_FLIP_NONE);
}

Turret::~Turret() {

}
