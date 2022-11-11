#pragma once
#include "PlayerBullet.h"

class NimbleBullet : public PlayerBullet{
public:
    NimbleBullet(int TarX, int TarY, const char *textureSheet, int x, int y, int sheetSizeXy, int numSprites);
    ~NimbleBullet();
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