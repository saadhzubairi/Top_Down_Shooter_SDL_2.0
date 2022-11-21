#pragma once

#include "../GameObject.h"

class BoomHit: public GameObject{
public:
    BoomHit(int x, int y);
    ~BoomHit();
    void Render() override;
    void Move() override;
    int life;
    int CurrSprite;
};

