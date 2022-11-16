#include "GameObject.h"
#include "HelperClasses/TextureManager.h"
#include "Game.h"


int GameObject::curSprite = 0;

GameObject::GameObject(const char *textureSheet, int x, int y, int sheetSizeXY, int numSprites, int spriteType) {

    this->spriteType = spriteType;

    switch (spriteType) {
        case 0:
            objTexture = TextureManager::loadSprite(textureSheet, sheetSizeXY, numSprites, gSpriteClips);
            break;
        case 1:
            objTexture = TextureManager::loadSprite1(textureSheet, sheetSizeXY, gSpriteClips);
            break;
        case 2:
            objTexture = TextureManager::loadSprite2(textureSheet, sheetSizeXY, numSprites, gSpriteClips);
            break;
    }
    xPos = x;
    yPos = y;
    tX = 0;
    tY = 0;
    fric = 0.95;
}

GameObject::~GameObject() {}

void GameObject::Update() {

    if (spriteType == 2) {
        destR.h = 256;
        destR.w = 256 * 3;
    } else if (spriteType == 1) {
        destR.h = destR.w = 256;
    }
    else {
        destR.h = 128;
        destR.w = 128;
    }
    destR.x = xPos - destR.w / 2;
    destR.y = yPos - destR.h / 2;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, &gSpriteClips[Counters::frame%3], &destR);
    /*if (Counters::frame % 60 == 0) {
        //printf("changed sprite @ %d frame, currsprite: %d\n",Counters::frame,curSprite);
        curSprite++;
        if (curSprite > 2) {
            curSprite = 0;
        }
    }*/
}

void GameObject::Destroy() {
    alive = false;
}

bool GameObject::isAlive() {
    return alive;
}

void GameObject::Move() {}

void GameObject::Translate(int x, int y) {
    this->tX = x;
    this->tY = y;
}

void GameObject::setObjTexture(const char *textureSheet, int sheetSizeXY, int numSprites) {
    objTexture = TextureManager::loadSprite(textureSheet, sheetSizeXY, numSprites, gSpriteClips);
}



