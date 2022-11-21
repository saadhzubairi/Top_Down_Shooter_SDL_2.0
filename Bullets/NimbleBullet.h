#pragma once

#include "DefaultBullet.h"

class NimbleBullet : public DefaultBullet {
public:
    NimbleBullet(int x, int y);

    ~NimbleBullet();

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