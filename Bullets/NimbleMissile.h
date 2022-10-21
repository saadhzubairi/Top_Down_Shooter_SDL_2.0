#pragma once
#include "PlayerBullet.h"

class NimbleMissile : public PlayerBullet{
public:
    NimbleMissile(int TarX, int TarY, const char *textureSheet, int x, int y, int sheetSizeXy, int numSprites);
    ~NimbleMissile();
    void Move() override;
private:
    int TarX;
    int TarY;
    int xFactor;
    int dX;
    int dY;
    float slope;
};