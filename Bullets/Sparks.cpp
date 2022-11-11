#include "Sparks.h"

int Sparks::life = 120;

Sparks::Sparks(const char *textureSheet, int x, int y, int sheetSizeXy, int numSprites)
        : GameObject(textureSheet, x, y, sheetSizeXy, numSprites) {
    this->xPos = x;
    this->yPos = y;
    this->fric = 0.95;
    this->tX = 0.0;
    this->tY = 0.0;
    SDL_SetTextureBlendMode(objTexture,SDL_BLENDMODE_BLEND);
}

Sparks::~Sparks() {

}

void Sparks::Render() {
    life--;
    int anti_life = 120 - life;
    SDL_SetTextureAlphaMod( objTexture, life);
    frame++;
    destR.h = destR.h*anti_life*0.01;
    destR.w = destR.w*anti_life*0.01;
    destR.x--;
    destR.y--;
    SDL_RenderCopy(Game::renderer, objTexture, &gSpriteClips[curSprite], &destR);
    if (frame % 60 == 0) {
        SDL_RenderPresent(Game::renderer);
        curSprite++;
        if (curSprite > 2) {
            curSprite = 0;
        }
    }
    if(life==0){
        Destroy();
    }
}

void Sparks::Move() {

}
