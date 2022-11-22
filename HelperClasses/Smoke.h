#pragma once

#include "../GameObject.h"

class Smoke : public GameObject{
public:
    Smoke(int x, int y);
    ~Smoke();
    void Render() override;
    void Move() override;
    int life;
    int CurrSprite;
};