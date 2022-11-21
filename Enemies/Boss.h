#pragma once

#include "../GameObject.h"
#include "../Game.h"
#include "Turret.h"

class Boss : public GameObject {
public:
    ~Boss();
    void Render() override;
    void RenderTurrets();
    void Move() override;
    void Update() override;
    Boss(int x, int y);
    Turret *turretll, *turretl, *turretr, *turretrr;
};
