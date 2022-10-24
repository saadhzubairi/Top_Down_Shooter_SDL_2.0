#pragma once


#include "../GameObject.h"

class PlayerBullet : public GameObject{

public:

    PlayerBullet(const char *textureSheet, int x, int y, int sheetSizeXy, int numSprites);
    ~PlayerBullet();
    void Move() override;
    void Render();
};