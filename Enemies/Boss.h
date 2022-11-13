
#pragma once

#include "../GameObject.h"
#include "../Game.h"

class Boss : public GameObject {
public:
    ~Boss();
    void Render() override;
    void Move();

    Boss(int x, int y);
};
