#pragma once

#include "SDL.h"
#include "UIElementsForGame/Counters.h"

class GameObject {

public:
    GameObject(const char *textureSheet, int x, int y, int sheetSizeXY, int numSprites, int spriteType);
    ~GameObject();

    virtual void Render();
    bool isAlive();
    void Destroy();
    virtual void Move() = 0;
    void Translate(int x, int y);

    int spriteType;
    int xPos, yPos;
    float fric, tX, tY;
    bool alive = true;

    void setObjTexture(const char *textureSheet,int sheetSizeXY,int numSprites);
    SDL_Texture *objTexture;
    SDL_Rect destR;
    SDL_Rect gSpriteClips[3];


    static int curSprite;

    void Update();
};