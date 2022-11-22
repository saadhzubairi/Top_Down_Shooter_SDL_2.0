#include "Smoke.h"

#include "../Game.h"

Smoke::Smoke(int x, int y) : GameObject(
        "../Assets/white_smoke.png", x, y, 768, 256, 1, 3, 0.25) {
    life = 0;
    CurrSprite = 0;
}

Smoke::~Smoke() {
}

void Smoke::Render() {
    SDL_RenderCopyEx(Game::renderer, objTexture, &spriteSourceRects[CurrSprite], &destR, 0, NULL, SDL_FLIP_NONE);
    life++;
    if(life%10 ==0) CurrSprite++;
    if (life > 30) {
        alive = false;
    }
}

void Smoke::Move() {}
