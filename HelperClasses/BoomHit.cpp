//
// Created by Saad Zubairi on 11/21/2022.
//

#include "BoomHit.h"
#include "../Game.h"

BoomHit::BoomHit(int x, int y)  : GameObject(
        "../Assets/boomHit.png", x, y, 768, 256, 1, 3, 0.25) {
    life = 0;
    CurrSprite = 0;
}

BoomHit::~BoomHit() {

}

void BoomHit::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, &spriteSourceRects[CurrSprite], &destR);
    life++;
    if(life%6 ==0) CurrSprite++;
    if (life > 18) {
        alive = false;
    }
}

void BoomHit::Move() {

}
