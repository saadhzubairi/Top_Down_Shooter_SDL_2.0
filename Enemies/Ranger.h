#include "../GameObject.h"

class Ranger : public GameObject{
public:
    Ranger(const char *textureSheet, int x, int y, int spriteSizeXY, int numSprites);
    ~Ranger();
    void Move() override;
    void TakeHit();
private:
    int life;
};