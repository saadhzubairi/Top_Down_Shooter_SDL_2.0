#pragma once

#include "PlayerBullet.h"

class EnemyBullet : public PlayerBullet {
public:
    EnemyBullet(const char *textureSheet, int x, int y, int sheetSizeXy, int numSprites);
    ~EnemyBullet();
    void Move() override;
};
