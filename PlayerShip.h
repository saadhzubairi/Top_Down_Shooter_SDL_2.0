#pragma once
#include "GameObject.h"

class PlayerShip : public GameObject{
public:
    PlayerShip(int x, int y);
    ~PlayerShip();
    void Move() override;
    bool hit;
    void TakeHit();
    int xVel=0;
    int yVel=0;

private:

};


