#pragma once
#include "DefaultBullet.h"
#include "../PlayerShip.h"
#include "../Game.h"

class RotatingBullet : public DefaultBullet{
public:
    RotatingBullet(int x, int y);
    ~RotatingBullet();
    void Move() override;
    void Render() override;

};
