#pragma once

#include "DefaultBullet.h"
#include "../Game.h"

class PlayerMissile : public DefaultBullet{
public:
    PlayerMissile(int x, int y, GameObject* enemy);
    ~PlayerMissile();
    void Move() override;
    void Render();
    GameObject* enemy;
    double xFactor;
    float dX;
    float dY;
    float slope;
    double angle;
    int life;
};
