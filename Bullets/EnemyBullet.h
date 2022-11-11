#pragma once

#include "DefaultBullet.h"

class EnemyBullet : public DefaultBullet {
public:
    EnemyBullet(int x, int y);

    ~EnemyBullet();

    void Move() override;
};
