#pragma once


#include "../GameObject.h"

class DefaultBullet : public GameObject{

public:

    DefaultBullet(int x, int y, int type);
    ~DefaultBullet();
    void Move() override;
    void Render();
};