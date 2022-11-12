#include "GameObject.h"
#include "HelperClasses/TextureManager.h"
#include "Game.h"


int GameObject::curSprite = 0;

GameObject::GameObject(const char *textureSheet, int x, int y,int sheetSizeXY,int numSprites) {
    objTexture = TextureManager::loadSprite(textureSheet, sheetSizeXY, numSprites, gSpriteClips);
    xPos = x;
    yPos = y;
    frame = 0;
    frame = 0;
}

GameObject::~GameObject() {}

void GameObject::Update() {
    destR.x = xPos;
    destR.y = yPos;
    destR.h = 128;
    destR.w = 128;
}

void GameObject::Render() {
    frame++;
    SDL_RenderCopy(Game::renderer, objTexture, &gSpriteClips[curSprite], &destR);
    if (frame % 20 == 0) {
        curSprite++;
        if (curSprite > 2) {
            curSprite = 0;
        }
    }
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

void GameObject::setObjTexture(const char *textureSheet,int sheetSizeXY,int numSprites) {
    objTexture = TextureManager::loadSprite(textureSheet, sheetSizeXY, numSprites, gSpriteClips);
}



