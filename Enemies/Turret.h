#pragma once
#include "../GameObject.h"
#include "../Game.h"

class Turret : public GameObject{
public:
    Turret(int x, int y);
    ~Turret();
    void Render() override;
    void Move();
};
