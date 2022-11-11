#pragma once

#include "DefaultBullet.h"

class NimbleBullet : public DefaultBullet {
public:
    NimbleBullet(int TarX, int TarY, int x, int y);

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