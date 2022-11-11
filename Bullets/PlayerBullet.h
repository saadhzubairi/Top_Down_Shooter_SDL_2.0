#pragma once
#include "DefaultBullet.h"

class PlayerBullet: public DefaultBullet {
public:
    PlayerBullet(int x, int y);
    ~PlayerBullet();
};
