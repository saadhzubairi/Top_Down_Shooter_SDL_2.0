#pragma once

#include "DefaultBullet.h"
#include "../Game.h"

class BossBullet : public DefaultBullet{
public:
    BossBullet(int x, int y);
    ~BossBullet();

    void Move() override;

    void Render() override;

private:
    double xFactor;
    double yFactor;
    float dX;
    float dY;
    float slope;
    double angle;
    bool isTurBul;
};
