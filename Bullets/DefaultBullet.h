#pragma once


#include "../GameObject.h"

class DefaultBullet : public GameObject{

public:
    int missile = 0;
    DefaultBullet(int x, int y, int type);
    ~DefaultBullet();
    void Move() override;
    void Update() override;
    void Render();
};