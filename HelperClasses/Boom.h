#pragma once
#include "../GameObject.h"

class Boom : public GameObject{
public:
    Boom(int x, int y);
    ~Boom();
    void Render() override;
    void Move() override;
    int life;
    int CurrSprite;
};
