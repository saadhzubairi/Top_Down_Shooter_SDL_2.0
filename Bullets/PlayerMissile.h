#pragma once

#include "DefaultBullet.h"

class PlayerMissile : public DefaultBullet{
public:
    PlayerMissile(int x, int y);
    ~PlayerMissile();
};


 /*#pragma once

class PlayerBullet: public DefaultBullet {
public:
    PlayerBullet(int x, int y);
    ~PlayerBullet();
};
*/