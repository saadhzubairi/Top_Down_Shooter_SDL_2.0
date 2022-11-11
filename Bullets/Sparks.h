#pragma once

#include "../GameObject.h"
#include "../Game.h"

class Sparks : public GameObject{
public:
    Sparks(const char *textureSheet, int x, int y, int sheetSizeXy, int numSprites);
    ~Sparks();
    void Render() override;
    void Move() override;
    static int life;
};
