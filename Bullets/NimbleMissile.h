#pragma once
#include "PlayerBullet.h"

class NimbleMissile : public PlayerBullet{
public:
    NimbleMissile(int TarX, int TarY, const char *textureSheet, int x, int y, int sheetSizeXy, int numSprites);
    ~NimbleMissile();
    void Move() override;
    void Render() override;
private:
    int TarX;
    int TarY;
    int xFactor;
    float dX;
    float dY;
    float slope;
};