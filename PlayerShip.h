#include "GameObject.h"

class PlayerShip : public GameObject{
public:
    PlayerShip(const char *textureSheet, int x, int y, int spriteSizeXY, int numSprites);
    ~PlayerShip();
    void Move() override;
    bool hit;
    void TakeHit();
private:

};


