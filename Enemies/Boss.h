
#pragma once

#include "../GameObject.h"
#include "../Game.h"
#include "Turret.h"

class Boss : public GameObject {
public:
    ~Boss();
    void Render() override;
    void Move();
    void Update() ;
    Boss(int x, int y);
    Turret *turretm;
    Turret *turretl;
    Turret *turretr;

};
