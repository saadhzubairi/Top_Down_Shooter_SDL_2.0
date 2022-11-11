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
    frame++;
    int xff = xFactor;
    SDL_RenderCopyEx(Game::renderer, objTexture, &gSpriteClips[curSprite], &destR, -xff * 7, NULL, SDL_FLIP_NONE);
    if (frame % 60 == 0) {
        SDL_RenderPresent(Game::renderer);
        curSprite++;
        if (curSprite > 2) {
            curSprite = 0;
        }
    }
}