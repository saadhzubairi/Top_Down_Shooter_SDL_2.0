//
// Created by Saad Zubairi on 11/21/2022.
//

#include <cstdio>
#include "Boom.h"
#include "../Game.h"

Boom::Boom(int x, int y) : GameObject(
        "../Assets/boom.png", x, y, 640, 256, 2, 5, 2) {
    life = 0;
    CurrSprite = 0;
}

Boom::~Boom() {
}

void Boom::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, &spriteSourceRects[CurrSprite], &destR);
    life++;
    if(life%6 ==0) CurrSprite++;
    if (life > 60) {
        alive = false;
    }
}

void Boom::Move() {}
